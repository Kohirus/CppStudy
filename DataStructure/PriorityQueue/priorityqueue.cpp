#include "PriorityQueue.hpp"
#include <iostream>
#include <cstring>
using namespace std;

PriorityQueue::PriorityQueue(int cap, Comp comp)
    : que_(new int[cap])
    , size_(0)
    , cap_(cap)
    , comp_(comp) {
}

PriorityQueue::~PriorityQueue() {
    delete[] que_;
    que_ = nullptr;
}

void PriorityQueue::push(int val) {
    if (size_ == cap_) expand(cap_ * 2);

    if (size_ == 0) {
        que_[size_] = val;
    } else {
        siftUp(size_, val);
    }
    size_++;
}

void PriorityQueue::pop() {
    if (size_ == 0)
        throw "priority queue is empty";
    size_--;
    if (size_ != 0) {
        siftDown(0, que_[size_]);
    }
}

int PriorityQueue::top() const {
    if (size_ == 0)
        throw "priority queue is empty";
    return que_[0];
}

int PriorityQueue::size() const {
    return size_;
}

bool PriorityQueue::empty() const {
    return size_ == 0;
}

void PriorityQueue::print() const {
    for (int i = 0; i < size_; i++) {
        cout << que_[i] << " ";
    }
    cout << endl;
}

void PriorityQueue::siftUp(int idx, int val) {
    while (idx > 0) {
        int father = (idx - 1) / 2;
        if (comp_(val, que_[father])) {
            que_[idx] = que_[father];
            idx       = father;
        } else {
            break;
        }
    }

    que_[idx] = val;
}

void PriorityQueue::siftDown(int idx, int val) {
    // 下沉时不能超过最后一个有孩子的节点
    while (idx < size_ / 2) {
        int child = 2 * idx + 1;
        if (child + 1 < size_ && comp_(que_[child + 1], que_[child])) {
            // 有右孩子 且右孩子的值大于左孩子 则将其更新为右孩子
            child++;
        }

        if (comp_(que_[child], val)) {
            que_[idx] = que_[child];
            idx       = child;
        } else {
            break;
        }
    }

    que_[idx] = val;
}

void PriorityQueue::expand(int size) {
    int* p = new int[size];
    memcpy(p, que_, cap_ * sizeof(int));
    delete[] que_;
    que_ = p;
    cap_ = size;
}
