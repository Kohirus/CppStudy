#include "hash.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

HashTable::HashTable(int size, double loadFactor)
    : useCnt_(0)
    , loadfactor_(loadFactor)
    , primeIdx_(0) {
    if (size != primes_[0]) {
        for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
            if (primes_[primeIdx_] >= size)
                break;
        }

        if (primeIdx_ == PRIME_SIZE) {
            primeIdx_--;
        }
    }

    table_.resize(primes_[primeIdx_]);
}

void HashTable::insert(int key) {
    double factor = useCnt_ * 1.0 / table_.size();
    if (factor > loadfactor_) {
        expand();
    }

    int idx = key % table_.size();
    if (table_[idx].empty()) {
        useCnt_++;
        table_[idx].emplace_front(key);
    } else {
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if (it == table_[idx].end()) {
            table_[idx].emplace_front(key);
        }
    }
}

void HashTable::remove(int key) {
    int  idx = key % table_.size();
    auto it  = ::find(table_[idx].begin(), table_[idx].end(), key);
    if (it != table_[idx].end()) {
        table_[idx].erase(it);
        if (table_[idx].empty()) {
            useCnt_--;
        }
    }
}

bool HashTable::find(int key) const {
    int  idx = key % table_.size();
    auto it  = ::find(table_[idx].begin(), table_[idx].end(), key);
    return it != table_[idx].end();
}

void HashTable::print() const {
    cout << "==================" << endl;
    for (int i = 0; i < table_.size(); i++) {
        cout << "[" << i << "] -> ";
        for (auto key : table_[i]) {
            cout << key << " -> ";
        }
        cout << endl;
    }
    cout << "==================" << endl;
}

void HashTable::expand() {
    if (primeIdx_ + 1 == PRIME_SIZE) {
        throw "Hashtable cannot expand anymore!";
    }

    primeIdx_++;
    useCnt_ = 0;

    vector<list<int>> oldTable;
    table_.swap(oldTable);
    table_.resize(primes_[primeIdx_]);

    for (auto list : oldTable) {
        for (auto key : list) {
            int idx = key % table_.size();
            if (table_[idx].empty()) {
                useCnt_++;
            }
            table_[idx].emplace_front(key);
        }
    }
}