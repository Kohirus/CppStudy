#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <vector>
using namespace std;

// 冒泡排序
void bubbleSort(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        bool flag = false;
        for (int j = 0; j < nums.size() - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                flag = true;
            }
        }
        if (!flag) return;
    }
}

// 选择排序
void selectionSort(vector<int>& nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        int minIdx = i, minVal = nums[i];
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < minVal) {
                minIdx = j;
                minVal = nums[j];
            }
        }
        if (i != minIdx) swap(nums[i], nums[minIdx]);
    }
}

#endif // !_BUFFER_SORT_H_