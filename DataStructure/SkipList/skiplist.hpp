#ifndef __SKIPLIST_HPP__
#define __SKIPLIST_HPP__

class SkipList {
public:
    SkipList();
    ~SkipList();

public:
    // 搜索数据
    bool find(int val);
    // 添加数据
    void add(int val);
    // 删除数据
    void remove(int val);
    // 打印跳表
    void print();

private:
    // 获取随机层数
    int getLevel() const;

    // 普通节点类型
    struct Node {
        Node(int data = int())
            : data_(data)
            , next_(nullptr)
            , down_(nullptr) { }
        int   data_; // 数据域
        Node* next_; // 指向同一层后一个节点的指针域
        Node* down_; // 指向下一层同一个节点的指针域
    };

    // 跳跃表的头节点类型
    struct HeadNode : public Node {
        HeadNode(int level)
            : level_(level) { }
        int level_; // 跳跃表的层数
    };

private:
    HeadNode* head_;
};

#endif // !__SKIPLIST_HPP__