/**
 * @file heap.cpp
 * @brief 大小根堆求解TopK的实现
 * @author Leaos
 * @date 2023-01-08
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

// #define DUPLICATE // 查询重复次数Top K
#define VALUE // 查询值Top K

#define DUPLICATE_CNT_MIN // 重复次数最小的前3个数字
#define DUPLICATE_CNT_MAX // 重复次数最大的前3个数字
#define VALUE_MIN         // 值最小的前5个数字
// #define VALUE_MAX         // 值最大的前5个数字

#ifdef DUPLICATE
int main() {
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        vec.push_back(rand() % 1000);
    }

#ifdef DUPLICATE_CNT_MIN
    // 统计重复次数最小的前3个数字
    int                     k = 3;
    unordered_map<int, int> map;
    for (auto key : vec) {
        map[key]++;
    }

    // 放入大根堆的时候，需要放key-value键值对
    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> maxheap(
        [](Type& a, Type& b) -> bool {
            return a.second < b.second;
        });

    auto it = map.begin();
    for (int i = 0; i < k; i++, ++it) {
        maxheap.push(*it);
    }

    for (; it != map.end(); ++it) {
        if (maxheap.top().second > it->second) {
            maxheap.pop();
            maxheap.push(*it);
        }
    }

    while (!maxheap.empty()) {
        cout << "key:" << maxheap.top().first
             << " cnt:" << maxheap.top().second << endl;
        maxheap.pop();
    }
#endif // DUPLICATE_CNT_MIN

#ifdef DUPLICATE_CNT_MAX
    // 统计重复次数最大的前3个数字
    int                     k = 3;
    unordered_map<int, int> map;
    for (auto key : vec) {
        map[key]++;
    }

    // 放入大根堆的时候，需要放key-value键值对
    using Type = pair<int, int>;
    using Comp = function<bool(Type&, Type&)>;
    priority_queue<Type, vector<Type>, Comp> minheap(
        [](Type& a, Type& b) -> bool {
            return a.second > b.second;
        });

    auto it = map.begin();
    for (int i = 0; i < k; i++, ++it) {
        minheap.push(*it);
    }

    for (; it != map.end(); ++it) {
        if (minheap.top().second < it->second) {
            minheap.pop();
            minheap.push(*it);
        }
    }

    while (!minheap.empty()) {
        cout << "key:" << minheap.top().first
             << " cnt:" << minheap.top().second << endl;
        minheap.pop();
    }
#endif // DUPLICATE_CNT_MAX
}

#endif // DUPLICATE

#ifdef VALUE

int main() {
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        vec.push_back(rand() % 10000);
    }

#ifdef VALUE_MIN

    // 求vec中值最小的前5个元素
    priority_queue<int> maxheap;
    int                 k = 5;

    // 由前k个元素构建一个大根堆
    for (int i = 0; i < 5; i++) {
        maxheap.push(vec[i]);
    }

    // 遍历剩余的元素直到最后
    for (int i = 5; i < vec.size(); i++) {
        if (maxheap.top() > vec[i]) {
            maxheap.pop();
            maxheap.push(vec[i]);
        }
    }

    // 输出结果
    while (!maxheap.empty()) {
        cout << maxheap.top() << " ";
        maxheap.pop();
    }
    cout << endl;
#endif // VALUE_MIN

#ifdef VALUE_MAX

    // 求vec中值最大的前5个元素
    priority_queue<int, vector<int>, greater<int>> minheap;
    int                                            k = 5;

    // 由前k个元素构建一个大根堆
    for (int i = 0; i < 5; i++) {
        minheap.push(vec[i]);
    }

    // 遍历剩余的元素直到最后
    for (int i = 5; i < vec.size(); i++) {
        if (minheap.top() < vec[i]) {
            minheap.pop();
            minheap.push(vec[i]);
        }
    }

    // 输出结果
    while (!minheap.empty()) {
        cout << minheap.top() << " ";
        minheap.pop();
    }
    cout << endl;
#endif // VALUE_MAX
}

#endif // VALUE