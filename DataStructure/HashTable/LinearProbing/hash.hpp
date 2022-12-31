/**
 * @file hash.hpp
 * @brief 线性探测哈希表的实现
 * @author Leaos
 * @date 2022-12-25
 */

#ifndef _HASH_H_
#define _HASH_H_

// 桶的状态
enum State {
    UNUSED = 0, // 未曾使用
    USING,      // 正在使用
    REMOVE,     // 已被删除
};

struct Bucket {
    Bucket(int key = 0, State state = UNUSED)
        : val_(key)
        , state_(state) { }

    int   val_;   // 存储的数据
    State state_; // 桶的当前状态
};

class HashTable {
public:
    HashTable(int size = primes_[0], double loadfactor = 0.75);
    ~HashTable();

    // 插入元素
    bool insert(int key);
    // 删除元素
    bool erase(int key);
    // 查询
    bool find(int key) const;
    // 打印
    void print() const;

private:
    // 扩容
    void expand();

private:
    Bucket* table_;      // 可动态扩容的数组
    int     tabSize_;    // 桶的总数量
    int     usedCnt_;    // 已使用的桶数量
    double  loadfactor_; // 装载因子
    int     primeIdx_;   // 素数表下标

    static const int PRIME_SIZE = 10;     // 素数表的大小
    static int       primes_[PRIME_SIZE]; // 素数表
};

#endif // !_HASH_H_