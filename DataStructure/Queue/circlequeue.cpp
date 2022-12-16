#include "circlequeue.hpp"
#include <string.h>
#include <iostream>
using namespace std;

CircleQueue::CircleQueue(int size)
    : que_(new int[size])
    , cap_(size)
    , front_(0)
    , rear_(0)
    , size_(0) {
}

CircleQueue::~CircleQueue() {
    delete[] que_;
    que_ = nullptr;
}

void CircleQueue::push(int val) {
    if ((rear_ + 1) % cap_ == front_) {
        expand(cap_ * 2);
    }
    que_[rear_] = val;
    rear_       = (rear_ + 1) % cap_;
    size_++;
}

void CircleQueue::pop() {
    if (front_ == rear_) {
        throw "Queue is empty";
    }
    front_ = (front_ + 1) % cap_;
    size_--;
}

int CircleQueue::front() const {
    if (front_ == rear_) {
        throw "Queue is empty";
    }
    return que_[front_];
}

int CircleQueue::back() const {
    if (front_ == rear_) {
        throw "Queue is empty";
    }
    return que_[(rear_ - 1 + cap_) % cap_];
}

bool CircleQueue::empty() const {
    return front_ == rear_;
}

int CircleQueue::size() const {
    return size_;
}

void CircleQueue::print() const {
    for (int i = front_; i != rear_; i = (i + 1) % cap_) {
        cout << que_[i] << " ";
    }
    cout << endl;
}

void CircleQueue::expand(int size) {
    int* ptr = new int[size];
    int  j   = 0;
    for (int i = front_; i != rear_; i = (i + 1) % cap_, j++) {
        ptr[j] = que_[i];
    }
    delete[] que_;

    que_   = ptr;
    cap_   = size;
    front_ = 0;
    rear_  = j;
}