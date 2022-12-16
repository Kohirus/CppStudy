/**
 * @file circlequeue.hpp
 * @brief 环形队列的实现
 * @author Leaos
 * @date 2022-12-16
 */

#ifndef _CIRCLEQUEUE_H_
#define _CIRCLEQUEUE_H_

class CircleQueue {
public:
    CircleQueue(int size = 10);
    ~CircleQueue();

    // 入队
    void push(int val);
    // 出队
    void pop();
    // 取队头元素
    int front() const;
    // 取队尾元素
    int back() const;
    // 队列是否为空
    bool empty() const;
    // 返回队列大小
    int size() const;
    // 打印
    void print() const;

private:
    // 扩容
    void expand(int size);

private:
    int* que_;
    int  cap_;   // 空间容量
    int  front_; // 队头
    int  rear_;  // 队尾
    int  size_;  // 队内元素个数
};

#endif // !_CIRCLEQUEUE_H_