/**
 * @file priorityqueue.hpp
 * @brief 优先级队列的实现
 * @author Leaos
 * @date 2022-12-21
 */

#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <functional>
using namespace std;

class PriorityQueue {
public:
    using Comp = function<bool(int, int)>;

    PriorityQueue(int cap = 20, Comp comp = greater<int>());
    ~PriorityQueue();

    // 入堆
    void push(int val);
    // 出堆
    void pop();
    // 获取堆顶元素
    int top() const;
    // 堆大小
    int size() const;
    // 堆是否为空
    bool empty() const;
    // 打印堆
    void print() const;

private:
    // 上浮操作
    void siftUp(int idx, int val);
    // 下沉操作
    void siftDown(int idx, int val);
    // 数组扩容
    void expand(int size);

private:
    int* que_;  // 动态扩容的数组
    int  size_; // 数组元素的个数
    int  cap_;  // 数组的总空间大小
    Comp comp_; // 比较器对象
};

#endif // !_RPIORITY_QUEUE_H_