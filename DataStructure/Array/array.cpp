#include "array.hpp"
#include <string.h>

Array::Array(int size)
    : mCur_(0)
    , mCap_(size) {
    mpArr_ = new int[mCap_];
}

Array::~Array() {
    delete[] mpArr_;
    mpArr_ = nullptr;
}

void Array::push_back(int val) {
    if (mCur_ == mCap_) {
        expand(2 * mCap_);
    }
    mpArr_[mCur_++] = val;
}

void Array::pop_back() {
    if (mCur_ != 0)
        mCur_--;
}

void Array::insert(int pos, int val) {
    if (pos < 0 || pos >= mCap_)
        return;

    if (mCur_ == mCap_) {
        expand(2 * mCap_);
    }

    for (int i = mCur_ - 1; i >= pos; i--) {
        mpArr_[i + 1] = mpArr_[i];
    }
    mpArr_[pos] = val;
    mCur_++;
}

void Array::erase(int pos) {
    if (pos < 0 || pos >= mCap_)
        return;
    for (int i = pos + 1; i < mCur_; i++) {
        mpArr_[i - 1] = mpArr_[i];
    }
    mCur_--;
}

int Array::find(int val) {
    for (int i = 0; i < mCur_; i++) {
        if (mpArr_[i] == val)
            return i;
    }
    return -1;
}

void Array::expand(int size) {
    int* ptr = new int[size];
    memcpy(ptr, mpArr_, sizeof(int) * mCap_);
    delete[] mpArr_;

    mpArr_ = ptr;
    mCap_  = size;
}