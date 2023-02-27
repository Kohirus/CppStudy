#include "kruskal.hpp"
#include <iostream>
using namespace std;

UnionFind::UnionFind(int size)
    : nums(size + 1) {
    for (int i = 0; i < size + 1; i++) {
        nums[i] = i;
    }
}

int UnionFind::find(int num) {
    if (nums[num] == num) {
        return num;
    }
    return nums[num] = find(nums[num]);
}

bool UnionFind::merge(int num1, int num2) {
    int idx1 = find(num1), idx2 = find(num2);
    if (idx1 != idx2) {
        nums[idx2] = idx1;
        return true;
    }
    return false;
}