#include "doublecirclelink.hpp"
#include <iostream>
using namespace std;

DoubleCircleLink::DoubleCircleLink()
    : head_(new Node()) {
    head_->next_ = head_;
    head_->prev_ = head_;
}

DoubleCircleLink::~DoubleCircleLink() {
    Node* cur = head_->next_;
    while (cur != head_) {
        head_->next_      = cur->next_;
        cur->next_->prev_ = head_;
        delete cur;
        cur = head_->next_;
    }
    delete head_;
    head_ = nullptr;
}

void DoubleCircleLink::push_back(int val) {
    Node* node          = new Node(val);
    head_->prev_->next_ = node;
    node->next_         = head_;
    node->prev_         = head_->prev_;
    head_->prev_        = node;
}

void DoubleCircleLink::push_front(int val) {
    Node* node   = new Node(val);
    Node* nxt    = head_->next_;
    node->next_  = nxt;
    node->prev_  = head_;
    nxt->prev_   = node;
    head_->next_ = node;
}

void DoubleCircleLink::remove(int val) {
    Node* cur = head_->next_;
    while (cur != head_) {
        if (cur->data_ == val) {
            cur->prev_->next_ = cur->next_;
            cur->next_->prev_ = cur->prev_;
            delete cur;
            break;
        }
        cur = cur->next_;
    }
}

bool DoubleCircleLink::find(int val) {
    Node* cur = head_->next_;
    while (cur != head_) {
        if (cur->data_ == val) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void DoubleCircleLink::print() const {
    Node* cur = head_->next_;
    while (cur != head_) {
        cout << cur->data_ << "->";
        cur = cur->next_;
    }
    cout << endl;
}