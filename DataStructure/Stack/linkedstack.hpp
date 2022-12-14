/**
 * @file linkedstack.hpp
 * @brief 链式栈的实现
 * @author Leaos
 * @date 2022-12-14
 */

#ifndef _LINKEDSTACK_H_
#define _LINKEDSTACK_H_

class LinkedStack {
public:
    LinkedStack();
    ~LinkedStack();

    // 出栈
    void push(int val);
    // 入栈
    void pop();
    // 返回栈顶
    int top() const;
    // 返回栈大小
    int size() const;
    // 栈是否为空
    bool empty() const;
    // 打印
    void print() const;

private:
    struct Node {
        Node(int data = 0)
            : data_(data)
            , next_(nullptr) {
        }
        int   data_;
        Node* next_;
    };

    Node* head_;
    int   size_;
};

#endif // !_LINKEDSTACK_H_