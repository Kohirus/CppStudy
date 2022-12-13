/**
 * @file slist.hpp
 * @brief 单链表的实现
 * @author Leaos
 * @date 2022-12-13
 */

// 链表节点定义
struct Node {
    Node(int val = 0)
        : data_(val)
        , next_(nullptr) { }
    int   data_;
    Node* next_;
};

class SList {
public:
    SList();
    ~SList();

public:
    // 尾插法
    void push_back(int val);
    // 头插法
    void push_front(int val);
    // 删除第一个值为 val 节点
    void remove(int val);
    // 删除所有值为 val 的节点
    void removeAll(int val);
    // 搜索是否存在值为 val 的元素
    bool find(int val);
    // 打印
    void print() const;

private:
    Node* head_; // 链表头节点
};