/**
 * @file hash.hpp
 * @brief 链地址哈希表的实现
 * @author Leaos
 * @date 2022-12-31
 */

#ifndef _HASH_H_
#define _HASH_H_

#include <vector>
#include <list>
using namespace std;

class HashTable {
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75);
    ~HashTable() = default;

    // 增加元素
    void insert(int key);
    // 删除元素
    void remove(int key);
    // 查找元素
    bool find(int key) const;
    // 打印
    void print() const;

private:
    // 扩容
    void expand();

private:
    vector<list<int>> table_;      // 哈希表
    int               useCnt_;     // 已使用的桶数量
    double            loadfactor_; // 装载因子
    int               primeIdx_;   // 素数表下标

    static const int PRIME_SIZE = 10;     // 素数表的大小
    static int       primes_[PRIME_SIZE]; // 素数表
};

#endif // !_HASH_H_