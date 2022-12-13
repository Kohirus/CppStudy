/**
 * @file circlelink.hpp
 * @brief 单向循环表的实现
 * @author Leaos
 * @date 2022-12-13
 */

#ifndef _CIRCLELINK_H_
#define _CIRCLELINK_H_

class CircleLink {
public:
    CircleLink();
    ~CircleLink();

public:
    // 尾插法
    void push_back(int val);
    // 头插法
    void push_front(int val);
    // 删除第一个值为 val 的节点
    void remove(int val);
    // 查询是否存在值为 val 的节点
    bool find(int val);
    // 打印
    void print() const;

private:
    struct Node {
        Node(int data = 0)
            : data_(data)
            , next_(nullptr) { }
        int   data_;
        Node* next_;
    };

    Node* head_;
    Node* tail_;
};

#endif // !_CIRCLELINK_H_