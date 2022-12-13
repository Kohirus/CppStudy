/**
 * @file doublecirclelink.hpp
 * @brief 双向循环链表的实现
 * @author Leaos
 * @date 2022-12-13
 */

#ifndef _DOUBLECIRCLELINK_H_
#define _DOUBLECIRCLELINK_H_

class DoubleCircleLink {
public:
    DoubleCircleLink();
    ~DoubleCircleLink();

    // 头插法
    void push_front(int val);
    // 尾插法
    void push_back(int val);
    // 删除
    void remove(int val);
    // 查找
    bool find(int val);
    // 打印
    void print() const;

private:
    // 节点类型
    struct Node {
        Node(int data = 0)
            : data_(data)
            , next_(nullptr)
            , prev_(nullptr) { }
        int   data_;
        Node* next_;
        Node* prev_;
    };

    Node* head_;
};

#endif // !_DOUBLECIRCLELINK_H_