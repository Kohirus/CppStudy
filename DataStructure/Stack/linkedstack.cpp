#include "linkedstack.hpp"
#include <iostream>
using namespace std;

LinkedStack::LinkedStack()
    : head_(new Node)
    , size_(0) {
}

LinkedStack::~LinkedStack() {
    Node* cur = head_->next_;
    while (cur) {
        head_->next_ = cur->next_;
        delete cur;
        cur = head_->next_;
    }
    delete head_;
}

void LinkedStack::push(int val) {
    Node* node   = new Node(val);
    node->next_  = head_->next_;
    head_->next_ = node;
    size_++;
}

void LinkedStack::pop() {
    if (size_ == 0) return;
    Node* node   = head_->next_;
    head_->next_ = node->next_;
    size_--;
    delete node;
}

int LinkedStack::top() const {
    if (size_ == 0)
        throw "Stack is empty";
    return head_->next_->data_;
}

int LinkedStack::size() const {
    return size_;
}

bool LinkedStack::empty() const {
    return size_ == 0;
}

void LinkedStack::print() const {
    Node* node = head_->next_;
    while (node) {
        cout << node->data_ << " ";
        node = node->next_;
    }
    cout << endl;
}