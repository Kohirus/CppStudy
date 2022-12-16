#include "linkedqueue.hpp"
#include <iostream>
using namespace std;

LinkedQueue::LinkedQueue()
    : head_(new Node(0))
    , tail_(head_)
    , size_(0) {
}

LinkedQueue::~LinkedQueue() {
    Node* cur = head_->next_;
    while (cur) {
        head_->next_ = cur->next_;
        delete cur;
        cur = head_->next_;
    }
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
}

void LinkedQueue::push(int val) {
    Node* node   = new Node(val);
    tail_->next_ = node;
    tail_        = node;
    size_++;
}

void LinkedQueue::pop() {
    if (size_ == 0)
        throw "Queue is empty";
    Node* node   = head_->next_;
    head_->next_ = node->next_;
    delete node;
    size_--;
    if (size_ == 0) {
        head_->next_ = head_;
        tail_        = head_;
    }
}

int LinkedQueue::front() const {
    if (head_->next_ == head_)
        throw "Queue is empty";
    return head_->next_->data_;
}

int LinkedQueue::back() const {
    return tail_->data_;
}

bool LinkedQueue::empty() const {
    return size_ == 0;
}

int LinkedQueue::size() const {
    return size_;
}

void LinkedQueue::print() const {
    if (head_->next_ == head_) return;
    Node* cur = head_->next_;
    while (cur) {
        cout << cur->data_ << "->";
        cur = cur->next_;
    }
    cout << endl;
}