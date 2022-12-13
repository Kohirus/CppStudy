#include "doublelink.hpp"
#include <iostream>
using namespace std;

DoubleLink::DoubleLink()
    : head_(new Node()) {
}

DoubleLink::~DoubleLink() {
    Node* cur = head_;
    while (cur) {
        head_ = head_->next_;
        delete cur;
        cur = head_;
    }
    head_ = nullptr;
}

void DoubleLink::push_back(int val) {
    Node* cur = head_;
    while (cur->next_ != nullptr) {
        cur = cur->next_;
    }
    Node* node  = new Node(val);
    cur->next_  = node;
    node->prev_ = cur;
    node->next_ = nullptr;
}

void DoubleLink::push_front(int val) {
    Node* node   = new Node(val);
    Node* nxt    = head_->next_;
    node->next_  = nxt;
    node->prev_  = head_;
    nxt->prev_   = node;
    head_->next_ = node;
}

void DoubleLink::remove(int val) {
    Node* cur = head_->next_;
    while (cur) {
        if (cur->data_ == val) {
            cur->prev_->next_ = cur->next_;
            if (cur->next_) {
                cur->next_->prev_ = cur->prev_;
            }
            delete cur;
            break;
        }
        cur = cur->next_;
    }
}

bool DoubleLink::find(int val) {
    Node* cur = head_->next_;
    while (cur) {
        if (cur->data_ == val) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void DoubleLink::print() const {
    Node* cur = head_->next_;
    while (cur) {
        cout << cur->data_ << "->";
        cur = cur->next_;
    }
    cout << endl;
}