/**
 * @file sequencestack.hpp
 * @brief 顺序栈的实现
 * @author Leaos
 * @date 2022-12-14
 */

#ifndef _SEQUENCESTACK_H_
#define _SEQUENCESTACK_H_

#include <vector>
using namespace std;

class SequenceStack {
public:
    SequenceStack(int size = 10);
    ~SequenceStack();

public:
    // 入栈
    void push(int val);
    // 出栈
    void pop();
    // 返回栈顶元素
    int top() const;
    // 栈是否为空
    bool empty() const;
    // 返回栈大小
    int size() const;
    // 打印
    void print() const;

private:
    // 数组扩容
    void expand(int size);

private:
    int* pStack_;
    int  top_; // 栈顶索引
    int  cap_; // 当前栈容量
};

#endif // !_SEQUENCESTACK_H_