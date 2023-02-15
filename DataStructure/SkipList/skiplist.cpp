#include "skiplist.hpp"
#include <iostream>
#include <cstdlib>
#include <unordered_map>
using namespace std;

SkipList::SkipList() {
    head_ = new HeadNode(1);
}

SkipList::~SkipList() {
    int level = head_->level_;
    for (int i = 0; i < level; i++) {
        Node* cur = head_->next_;
        while (cur != nullptr) {
            Node* tmp = cur->next_;
            delete cur;
            cur = tmp;
        }
        cur   = head_;
        head_ = static_cast<HeadNode*>(head_->down_);
        delete cur;
    }
}

bool SkipList::find(int val) {
    Node *pre = head_, *cur = pre->next_;
    for (;;) {
        if (cur != nullptr) {
            if (cur->data_ < val) {
                pre = cur;
                cur = cur->next_;
                continue;
            } else if (cur->data_ == val) {
                return true;
            }
        }

        if (pre->down_ == nullptr) {
            // 此时遍历到了第一层 都没有找到该节点
            break;
        }

        pre = pre->down_;
        cur = pre->next_;
    }
    return false;
}

void SkipList::add(int val) {
    if (find(val)) return;

    int level = getLevel();
    // level过大时 只增长一层
    if (level > head_->level_) {
        level           = head_->level_ + 1;
        HeadNode* hnode = new HeadNode(level);
        hnode->down_    = head_;
        head_           = hnode;
    }

    // 创建level层的data节点 修改down_指针域
    Node** nodelist = new Node*[level];
    for (int i = level - 1; i >= 0; i--) {
        nodelist[i] = new Node(val);
        if (i < level - 1) {
            nodelist[i]->down_ = nodelist[i + 1];
        }
    }

    Node* head = head_;
    for (int i = head_->level_; i > level; i--) {
        head = head->down_;
    }

    Node *pre = head, *cur = pre->next_;
    for (int i = 0; i < level; i++) {
        while (cur != nullptr && cur->data_ < val) {
            pre = cur;
            cur = cur->next_;
        }

        // 新节点插入到pre和cur之间
        nodelist[i]->next_ = cur;
        pre->next_         = nodelist[i];

        pre = pre->down_;
        if (pre != nullptr) {
            cur = pre->next_;
        }
    }

    delete[] nodelist;
    nodelist = nullptr;
}

void SkipList::remove(int val) {
    Node *pre = head_, *cur = pre->next_;

    for (;;) {
        if (cur != nullptr) {
            if (cur->data_ < val) {
                pre = cur;
                cur = cur->next_;
                continue;
            } else if (cur->data_ == val) {
                // 删除cur指向的节点
                pre->next_ = cur->next_;
                delete cur;
            }
        }

        if (pre->down_ == nullptr) {
            break;
        }

        pre = pre->down_;
        if (head_->next_ == nullptr) {
            delete head_;
            head_ = static_cast<HeadNode*>(pre);
        }
        cur = pre->next_;
    }
}

int SkipList::getLevel() const {
    int level = 1;
    while (rand() % 2 == 1) {
        level++;
    }
    return level;
}

void SkipList::print() {
    Node* head = head_;
    while (head != nullptr) {
        Node* cur = head->next_;
        while (cur != nullptr) {
            cout << cur->data_ << " ";
            cur = cur->next_;
        }
        cout << endl;
        head = head->down_;
    }
}