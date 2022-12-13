#include "slist.hpp"
#include <iostream>
using namespace std;

SList::SList()
    : head_(new Node) {
}

SList::~SList() {
    while (head_->next_ != nullptr) {
        Node* node   = head_->next_;
        head_->next_ = node->next_;
        delete node;
    }
    delete head_;
    head_ = nullptr;
}

void SList::push_back(int val) {
    Node* cur = head_;
    while (cur->next_ != nullptr) {
        cur = cur->next_;
    }
    cur->next_ = new Node(val);
}

void SList::push_front(int val) {
    Node* node   = new Node(val);
    node->next_  = head_->next_;
    head_->next_ = node;
}

void SList::remove(int val) {
    Node* cur = head_;
    while (cur->next_ != nullptr) {
        if (cur->next_->data_ == val) {
            Node* node = cur->next_;
            cur->next_ = node->next_;
            delete node;
            break;
        }
        cur = cur->next_;
    }
}

void SList::removeAll(int val) {
    Node* cur = head_;
    while (cur && cur->next_ != nullptr) {
        if (cur->next_->data_ == val) {
            Node* node = cur->next_;
            cur->next_ = node->next_;
            delete node;
        } else {
            cur = cur->next_;
        }
    }
}

bool SList::find(int val) {
    Node* cur = head_->next_;
    while (cur) {
        if (cur->data_ == val) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void SList::print() const {
    Node* cur = head_->next_;
    while (cur != nullptr) {
        cout << cur->data_ << "->";
        cur = cur->next_;
    }
    cout << endl;
}