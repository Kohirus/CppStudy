#include "circlelink.hpp"
#include <iostream>
using namespace std;

CircleLink::CircleLink()
    : head_(new Node()) {
    tail_->next_ = head_;
    head_->next_ = head_;
}

CircleLink::~CircleLink() {
    Node* cur = head_->next_;
    while (cur != head_) {
        head_->next_ = cur->next_;
        delete cur;
        cur = head_->next_;
    }
    delete head_;
    head_ = nullptr;
}

void CircleLink::push_back(int val) {
    Node* node   = new Node(val);
    node->next_  = tail_->next_;
    tail_->next_ = node;
    tail_        = node;
    if (head_->next_ == head_) {
        head_->next_ = node;
    }
}

void CircleLink::push_front(int val) {
    Node* node   = new Node(val);
    node->next_  = head_->next_;
    head_->next_ = node;
    if (node->next_ == head_) {
        tail_ = node;
    }
}

void CircleLink::remove(int val) {
    if (head_->next_ == head_) return;
    Node* cur = head_;
    while (cur->next_ != tail_) {
        if (cur->next_->data_ == val) {
            Node* nxt  = cur->next_;
            cur->next_ = nxt->next_;
            delete nxt;
            return;
        }
        cur = cur->next_;
    }
    if (tail_->data_ == val) {
        cur->next_ = tail_->next_;
        delete tail_;
        tail_ = cur;
    }
}

bool CircleLink::find(int val) {
    Node* cur = head_->next_;
    while (cur != head_) {
        if (cur->data_ == val)
            return true;
        cur = cur->next_;
    }
    return false;
}

void CircleLink::print() const {
    Node* cur = head_->next_;
    while (cur != head_) {
        cout << cur->data_ << "->";
        cur = cur->next_;
    }
    cout << endl;
}