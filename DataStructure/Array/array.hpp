/**
 * @file arary.hpp
 * @brief 可扩容数组的实现
 * @author Leaos
 * @date 2022-12-11
 */

#ifndef _ARRAY_H_
#define _ARRAY_H_

class Array {
public:
    Array(int size = 10);
    ~Array();

public:
    // 返回第i个位置的值
    int at(int idx) const { return mpArr_[idx]; }
    // 返回数组大小
    int size() const { return mCur_; }
    // 在末尾增加元素
    void push_back(int val);
    // 删除末尾元素
    void pop_back();
    // 按位置增加元素
    void insert(int pos, int val);
    // 按位置删除
    void erase(int pos);
    // 元素查询
    int find(int val);
    // 数组扩容
    void expand(int size);

private:
    int* mpArr_; // 指向可扩容数组的内存
    int  mCap_;  // 数组的容量
    int  mCur_;  // 数组有效元素的个数
};

#endif // !_ARRAY_H_