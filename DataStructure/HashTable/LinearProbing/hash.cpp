#include "hash.hpp"
#include <iostream>
using namespace std;

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

HashTable::HashTable(int size, double loadfactor)
    : usedCnt_(0)
    , loadfactor_(loadfactor)
    , primeIdx_(0) {
    // 将其调整到最近的素数
    if (size != primes_[0]) {
        for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
            if (primes_[primeIdx_] > size) {
                break;
            }
        }
    }
    // 如果size过大 已超过最后一个素数 则调整为最后一个素数
    if (primeIdx_ == PRIME_SIZE) {
        primeIdx_--;
    }

    tabSize_ = primes_[primeIdx_];
    table_   = new Bucket[tabSize_];
}

HashTable::~HashTable() {
    delete[] table_;
    table_ = nullptr;
}

bool HashTable::insert(int key) {
    double factor = usedCnt_ * 1.0 / tabSize_;
    if (factor > loadfactor_) {
        // 哈希表扩容
        expand();
    }

    int idx = key % tabSize_;

    int i = idx;
    do {
        if (table_[i].state_ != USING) {
            table_[i].state_ = USING;
            table_[i].val_   = key;
            usedCnt_++;
            return true;
        }
        i = (i + 1) % tabSize_;
    } while (i != idx);

    return false;
}

bool HashTable::erase(int key) {
    int idx = key % tabSize_;

    int i = idx;
    do {
        if (table_[i].state_ == USING && table_[i].val_ == key) {
            table_[i].state_ = REMOVE;
            usedCnt_--;
        }
        i = (i + 1) % tabSize_;
    } while (table_[i].state_ != UNUSED && i != idx);

    return true;
}

bool HashTable::find(int key) const {
    int idx = key % tabSize_;

    int i = idx;
    do {
        if (table_[i].state_ == USING && table_[i].val_ == key) {
            return true;
        }
        i = (i + 1) % tabSize_;
    } while (table_[i].state_ != UNUSED && i != idx);

    return false;
}

void HashTable::print() const {
    for (int i = 0; i < tabSize_; i++) {
        if (table_[i].state_ == USING) {
            cout << table_[i].val_ << " ";
        } else {
            cout << "x ";
        }
    }
    cout << endl;
}

void HashTable::expand() {
    ++primeIdx_;
    if (primeIdx_ == PRIME_SIZE) {
        throw "HashTable is too large! Can't expand anymore!";
    }

    Bucket* newTable = new Bucket[primes_[primeIdx_]];
    for (int i = 0; i < tabSize_; i++) {
        if (table_[i].state_ == USING) {
            int idx = table_[i].val_ % primes_[primeIdx_];

            int k = idx;
            do {
                if (newTable[k].state_ != USING) {
                    newTable[k].state_ = USING;
                    newTable[k].val_   = table_[i].val_;
                    break;
                }
                k = (k + 1) % primes_[primeIdx_];
            } while (k != idx);
        }
    }

    delete[] table_;
    table_   = newTable;
    tabSize_ = primes_[primeIdx_];
}