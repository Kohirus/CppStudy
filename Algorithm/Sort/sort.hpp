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

// 插入排序
void insertionSort(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        int val = nums[i], j = i - 1;
        for (; j >= 0; j--) {
            if (nums[j] <= val) {
                break;
            }
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = val;
    }
}

// 希尔排序
void shellSort(vector<int>& nums) {
    for (int gap = nums.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < nums.size(); i++) {
            int val = nums[i], j = i - gap;
            for (; j >= 0; j -= gap) {
                if (nums[j] <= val) {
                    break;
                }
                nums[j + gap] = nums[j];
            }
            nums[j + gap] = val;
        }
    }
}

#endif // !_BUFFER_SORT_H_