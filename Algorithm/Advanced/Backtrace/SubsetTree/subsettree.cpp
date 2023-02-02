/**
 * @file subsettree.cpp
 * @brief 子集树的实现
 * @author Leaos
 * @date 2023-02-01
 */

#include <iostream>
#include <vector>
using namespace std;

void subsetTree(const vector<int>& nums, vector<bool>& used, int idx) {
    if (idx == nums.size()) { // 递归结束的条件
        for (int j = 0; j < nums.size(); j++) {
            if (used[j])
                cout << nums[j] << " ";
        }
        cout << endl;
    } else {
        used[idx] = true; // 选择左孩子
        subsetTree(nums, used, idx + 1);

        used[idx] = false; // 选择右孩子
        subsetTree(nums, used, idx + 1);
    }
}

int main() {
    vector<int>  nums = { 1, 2, 3 };
    vector<bool> used(nums.size(), false);
    subsetTree(nums, used, 0);
    return 0;
}