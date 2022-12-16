/**
 * @file linkedqueue.hpp
 * @brief 链式队列的实现
 * @author Leaos
 * @date 2022-12-16
 */

#ifndef _LINKEDQUEUE_H_
#define _LINKEDQUEUE_H_

class LinkedQueue {
public:
    LinkedQueue();
    ~LinkedQueue();

    // 入队
    void push(int val);
    // 出队
    void pop();
    // 返回队头元素
    int front() const;
    // 返回队尾元素
    int back() const;
    // 队列是否为空
    bool empty() const;
    // 返回队列大小
    int size() const;
    // 打印队列
    void print() const;

private:
    struct Node {
        Node(int data)
            : data_(data)
            , next_(nullptr) { }
        int   data_;
        Node* next_;
    };

    Node* head_;
    Node* tail_;
    int   size_;
};

#endif // !_LINKEDQUEUE_H_