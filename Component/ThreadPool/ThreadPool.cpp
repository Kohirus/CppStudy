#include "ThreadPool.hpp"
#include <thread>
#include <iostream>

const int TASK_MAX_THRESHHOLD   = 1024;
const int THREAD_MAX_THRESHHOLD = 10;
const int THREAD_MAX_IDLE_TIME  = 60;

Semaphore::Semaphore(int limit)
    : resLimit_(limit) {
}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mtx_);
    cond_.wait(lock, [&]() -> bool { return resLimit_ > 0; });
    resLimit_--;
}

void Semaphore::post() {
    std::unique_lock<std::mutex> lock(mtx_);
    resLimit_++;
    cond_.notify_all();
}

Task::Task()
    : result_(nullptr) {
}

void Task::exec() {
    if (result_ != nullptr) {
        result_->setVal(run());
    }
}

Result::Result(std::shared_ptr<Task> task, bool isValid)
    : task_(task)
    , sem_(0)
    , isValid_(isValid) {
    task_->setResult(this);
}

Any Result::get() {
    if (!isValid_) {
        return "";
    }

    sem_.wait();
    return std::move(any_);
}

void Result::setVal(Any any) {
    this->any_ = std::move(any);
    sem_.post();
}

Thread::Thread(ThreadFunc func)
    : func_(std::move(func))
    , threadId_(generateId_++) {
}

Thread::~Thread() {
}

void Thread::start() {
    // 创建一个线程来执行线程函数
    std::thread t(func_, threadId_);
    t.detach();
}

int Thread::getId() const {
    return threadId_;
}

int Thread::generateId_ = 0;

ThreadPool::ThreadPool()
    : initThreadSize_(0)
    , curThreadSize_(0)
    , threadSizeThreshHold_(THREAD_MAX_THRESHHOLD)
    , idleThreadSize_(0)
    , taskSize_(0)
    , taskQueMaxThreshHold_(TASK_MAX_THRESHHOLD)
    , poolMode_(PoolMode::MODE_FIXED)
    , isPoolingRunning_(false) {
}

ThreadPool::~ThreadPool() {
    isPoolingRunning_ = false;

    // 等待线程池中的所有线程返回
    std::unique_lock<std::mutex> lock(taskQueMutex_);
    notEmpty_.notify_all();
    exitCond_.wait(lock, [&]() -> bool { return curThreadSize_ == 0; });
}

void ThreadPool::start(int initThreadSize) {
    isPoolingRunning_ = true;
    initThreadSize_   = initThreadSize;
    curThreadSize_    = initThreadSize;

    // 创建线程对象
    for (int i = 0; i < initThreadSize_; i++) {
        auto ptr      = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
        int  threadId = ptr->getId();
        threads_.emplace(threadId, std::move(ptr));
    }

    // 启动所有线程
    for (int i = 0; i < initThreadSize_; i++) {
        threads_[i]->start();
        idleThreadSize_++; // 记录初始空闲线程的数量
    }
}

void ThreadPool::setMode(PoolMode mode) {
    if (checkRunningState())
        return;
    poolMode_ = mode;
}

void ThreadPool::setTaskQueMaxThreshHold(int threshHold) {
    if (checkRunningState())
        return;
    taskQueMaxThreshHold_ = threshHold;
}

void ThreadPool::setThreadMaxThreshHold(int threshHold) {
    if (checkRunningState())
        return;
    if (poolMode_ == PoolMode::MODE_CACHED) {
        threadSizeThreshHold_ = threshHold;
    }
}

Result ThreadPool::submitTask(std::shared_ptr<Task> sp) {
    std::unique_lock<std::mutex> lock(taskQueMutex_);

    // 使用 Lambda 表达式传入匿名函数对象 直到队列大小小于上限阈值时才唤醒该条件变量
    // wait_for 则设定了阻塞时间 超时则返回
    if (!notFull_.wait_for(lock, std::chrono::seconds(1),
            [&]() -> bool { return taskQue_.size() < taskQueMaxThreshHold_; })) {
        // 阻塞超时 条件变量依然没有满足
        std::cerr << "Task queue is full! Failed to submit task!" << std::endl;
        return Result(sp, false);
    }

    taskQue_.emplace(sp);
    taskSize_++;

    // 通知阻塞在该条件变量上的线程 以执行新的任务
    notEmpty_.notify_all();

    // 工作在 cache 模式下 && 任务数量>空闲线程数量 && 当前总线程数量<线程数量阈值
    if (poolMode_ == PoolMode::MODE_CACHED && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeThreshHold_) {
        // 创建新的线程
        auto ptr      = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
        int  threadId = ptr->getId();
        threads_.emplace(threadId, std::move(ptr));
        threads_[threadId]->start(); // 启动线程
        curThreadSize_++;
        idleThreadSize_++;
    }

    return Result(sp);
}

void ThreadPool::threadFunc(int threadId) {
    auto lastTime = std::chrono::high_resolution_clock::now();

    for (;;) {
        std::shared_ptr<Task> task;
        {
            std::unique_lock<std::mutex> lock(taskQueMutex_);

            // 每秒返回 1 次
            while (taskQue_.size() == 0) {
                if (!isPoolingRunning_) {
                    threads_.erase(threadId);
                    exitCond_.notify_all();
                    return;
                }

                // 对多余的线程进行回收 空闲时间超过60s则回收线程资源
                if (poolMode_ == PoolMode::MODE_CACHED) {
                    if (std::cv_status::timeout == notEmpty_.wait_for(lock, std::chrono::seconds(1))) {
                        auto now = std::chrono::high_resolution_clock::now();
                        auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
                        if (dur.count() >= THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_) {
                            // 回收当前线程
                            threads_.erase(threadId);
                            curThreadSize_--;
                            initThreadSize_--;
                            return;
                        }
                    }
                } else {
                    notEmpty_.wait(lock);
                }

                /*
                if (!isPoolingRunning_) {
                    // 线程池结束 回收线程资源
                    threads_.erase(threadId);
                    exitCond_.notify_all();
                    return;
                }
                */
            }

            initThreadSize_--;

            task = taskQue_.front();
            taskQue_.pop();
            taskSize_--;

            // 如果任务队列中还有剩余任务 通知其他线程以处理任务�
            if (!taskQue_.empty()) notEmpty_.notify_all();

            notFull_.notify_all();
        }

        if (task != nullptr) {
            task->exec();
        }

        initThreadSize_++;
        lastTime = std::chrono::high_resolution_clock::now(); // 更新线程工作完成的时间点
    }
}

bool ThreadPool::checkRunningState() const {
    return isPoolingRunning_;
}
