#include "sequencestack.hpp"
#include <iostream>
#include <string.h>
using namespace std;

SequenceStack::SequenceStack(int size)
    : pStack_(new int[size])
    , top_(0)
    , cap_(size) {
}

SequenceStack::~SequenceStack() {
    delete[] pStack_;
    pStack_ = nullptr;
}

void SequenceStack::push(int val) {
    if (top_ == cap_)
        expand(cap_ * 2);
    pStack_[top_++] = val;
}

void SequenceStack::pop() {
    if (top_ == 0) return;
    top_--;
}

int SequenceStack::top() const {
    if (top_ == 0)
        throw "Stack is empty";
    return pStack_[top_ - 1];
}

bool SequenceStack::empty() const {
    return top_ == 0;
}

int SequenceStack::size() const {
    return top_;
}

void SequenceStack::print() const {
    for (int i = top_ - 1; i >= 0; i--) {
        cout << pStack_[i] << " ";
    }
    cout << endl;
}

void SequenceStack::expand(int size) {
    int* p = new int[size];
    memcpy(p, pStack_, top_ * sizeof(int));
    delete[] pStack_;
    pStack_ = p;
    cap_    = size;
}