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

// 快速排序的分割函数
int partation(vector<int>& nums, int left, int right) {
    int val = nums[left];

    while (left < right) {
        while (left < right && nums[right] > val) right--;
        if (left < right) {
            nums[left] = nums[right];
            left++;
        }

        while (left < right && nums[left] < val) left++;
        if (left < right) {
            nums[right] = nums[left];
            right--;
        }
    }

    nums[left] = val;
    return left;
}

// 快速排序的递归函数
void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int pos = partation(nums, left, right);

    quickSort(nums, left, pos - 1);
    quickSort(nums, pos + 1, right);
}

// 快速排序
void quickSort(vector<int>& nums) {
    quickSort(nums, 0, nums.size() - 1);
}

// 将 [left, mid] 和 [mid+1, right] 这两个有序序列合并为一个有序序列
void merge(vector<int>& nums, int left, int mid, int right) {
    int* tmp = new int[right - left + 1];
    int  i = left, j = mid + 1, idx = 0;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmp[idx++] = nums[i++];
        } else {
            tmp[idx++] = nums[j++];
        }
    }

    while (i <= mid) tmp[idx++] = nums[i++];
    while (j <= right) tmp[idx++] = nums[j++];

    for (i = left, j = 0; i <= right; i++, j++) {
        nums[i] = tmp[j];
    }
    delete[] tmp;
}

// 归并排序的递归函数
void mergeSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);

    merge(nums, left, mid, right);
}

// 归并排序
void mergeSort(vector<int>& nums) {
    mergeSort(nums, 0, nums.size() - 1);
}

// 堆的下沉操作
void siftDown(vector<int>& nums, int idx, int size) {
    int val = nums[idx];
    // 下沉时不能超过最后一个有孩子的节点
    while (idx < size / 2) {
        int child = 2 * idx + 1;
        if (child + 1 < size && nums[child + 1] > nums[child]) {
            // 有右孩子 且右孩子的值大于左孩子 则将其更新为右孩子
            child++;
        }

        if (nums[child] > val) {
            nums[idx] = nums[child];
            idx       = child;
        } else {
            break;
        }
    }

    nums[idx] = val;
}

// 堆排序
void heapSort(vector<int>& nums) {
    int endIdx = nums.size() - 1; // 最后一个元素的索引
    // 从第一个非叶子节点开始
    for (int i = (endIdx - 1) / 2; i >= 0; i--) {
        siftDown(nums, i, nums.size());
    }

    for (int i = endIdx; i > 0; i--) {
        swap(nums[0], nums[i]);
        siftDown(nums, 0, i);
    }
}

#endif // !_BUFFER_SORT_H_