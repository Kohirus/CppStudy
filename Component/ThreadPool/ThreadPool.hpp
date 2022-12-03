#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <memory>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <thread>

class Any {
public:
    Any()                      = default;
    ~Any()                     = default;
    Any(const Any&)            = delete;
    Any& operator=(const Any&) = delete;
    Any(Any&&)                 = default;
    Any& operator=(Any&&)      = default;

    template <typename T>
    Any(T data)
        : base_(std::make_unique<Derive<T>>(data)) { }

    template <typename T>
    T cast_() {
        Derive<T>* pd = dynamic_cast<Derive<T>*>(base_.get());
        if (pd == nullptr) {
            throw "type is unmatch!";
        }
        return pd->data_;
    }

private:
    class Base {
    public:
        virtual ~Base() = default;
    };

    template <typename T>
    class Derive : public Base {
    public:
        Derive(T data)
            : data_(data) { }
        T data_;
    };

private:
    std::unique_ptr<Base> base_;
};

// 信号量类
class Semaphore {
public:
    Semaphore(int limit);
    ~Semaphore() = default;

    // 获取一个信号量资源
    void wait();
    // 增加一个信号量资源
    void post();

private:
    int                     resLimit_;
    std::mutex              mtx_;
    std::condition_variable cond_;
};

class Result;

// 抽象任务基类
class Task {
public:
    Task();
    ~Task() = default;

    void        exec();
    virtual Any run() = 0;
    void        setResult(Result* res) { result_ = res; }

private:
    Result* result_;
};

// 线程池的工作模式
enum class PoolMode {
    MODE_FIXED,  // 固定大小的线程池
    MODE_CACHED, // 可变大小的线程池
};

// 线程池的 Task 执行完成后的返回值
class Result {
public:
    Result(std::shared_ptr<Task> task, bool isValid = true);
    ~Result() = default;

    Any  get();
    void setVal(Any any);

private:
    Any                   any_;     // 存储任务的返回值
    Semaphore             sem_;     // 线程通信的信号量
    std::shared_ptr<Task> task_;    // ָ执行对应的任务对象
    std::atomic_bool      isValid_; // 返回值是否有效
};

// 线程类型
class Thread {
public:
    // 线程函数对象类型
    using ThreadFunc = std::function<void(int)>;

    Thread(ThreadFunc func);
    ~Thread();
    // 启动线程
    void start();
    // 获取线程id
    int getId() const;

private:
    ThreadFunc func_;     // 线程函数
    int        threadId_; // 线程ID
    static int generateId_;
};

// 线程池类型
class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();
    ThreadPool(const ThreadPool&)            = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 开启线程池
    void start(int initThreadSize = std::thread::hardware_concurrency());
    // 设置线程池的工作模式
    void setMode(PoolMode mode);
    // 设置任务队列的上限阈值
    void setTaskQueMaxThreshHold(int threshHold);
    // 设置线程数量的上限阈值
    void setThreadMaxThreshHold(int threshHold);
    // 给线程池提交任务
    Result submitTask(std::shared_ptr<Task> sp);

private:
    // 线程函数
    void threadFunc(int threadId);
    // 检查线程池的运行状态
    bool checkRunningState() const;

private:
    std::unordered_map<int, std::unique_ptr<Thread>> threads_; // 线程集合

    size_t          initThreadSize_;       // 初始线程数量
    std::atomic_int curThreadSize_;        // 当前线程池的的线程总数量
    std::atomic_int idleThreadSize_;       // 当前线程池里的空闲线程的数量
    int             threadSizeThreshHold_; // 线程数量的上限阈值

    std::queue<std::shared_ptr<Task>> taskQue_;              // 任务队列
    std::atomic_uint                  taskSize_;             // 任务数量
    int                               taskQueMaxThreshHold_; // 任务队列的上限阈值
    std::mutex                        taskQueMutex_;         // 保证任务队列的线程安全
    std::condition_variable           notFull_;              // 表示任务队列不为满
    std::condition_variable           notEmpty_;             // 表示任务队列不为空
    std::condition_variable           exitCond_;             // 等待线程资源全部回收

    PoolMode         poolMode_;         // 当前线程池的工作模式
    std::atomic_bool isPoolingRunning_; // 标识线程池是否已经启动
};

#endif // _THREAD_POOL_H_