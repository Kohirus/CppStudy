#include "unionfind.hpp"
#include <iostream>
using namespace std;

UnionFind::UnionFind(int size)
    : nums(size + 1)
    , ranks(size + 1, 1) {
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

void UnionFind::merge(int num1, int num2) {
    int idx1 = find(num1), idx2 = find(num2);
    if (idx1 != idx2) {
        if (ranks[idx1] > ranks[idx2]) {
            nums[idx2] = idx1;
        } else {
            if (ranks[idx1] == ranks[idx2]) {
                ranks[idx2]++;
            }
            nums[idx1] = idx2;
        }
    }
}

void UnionFind::print() {
    cout << "Index: ";
    for (int i = 0; i < nums.size(); i++) {
        cout << i << " ";
    }
    cout << endl;
    cout << "Nums:  ";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "Ranks: ";
    for (int i = 0; i < ranks.size(); i++) {
        cout << ranks[i] << " ";
    }
    cout << endl;
}