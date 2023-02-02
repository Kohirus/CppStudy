/**
 * @file sorttree.cpp
 * @brief 排列树的实现
 * @author Leaos
 * @date 2023-02-02
 */

#include <iostream>
#include <vector>
using namespace std;

void sortTree(vector<int>& nums, int idx) {
    if (idx == nums.size()) {
        for (int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    } else {
        // 进入孩子节点
        for (int i = idx; i < nums.size(); i++) {
            swap(nums[i], nums[idx]);
            sortTree(nums, idx + 1);
            // 回退到父节点
            swap(nums[i], nums[idx]);
        }
    }
}

int main() {
    vector<int> nums = { 1, 2, 3, 4 };
    sortTree(nums, 0);
    return 0;
}