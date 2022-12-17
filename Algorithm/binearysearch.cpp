#include <iostream>
#include <vector>
using namespace std;

// 非递归 左闭有闭
int binearySearch1(const vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

// 非递归 左闭右开
int binearySearch2(const vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + ((right - left) / 2);
        if (nums[mid] > target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// 递归版本
int binearySearch3(const vector<int>& nums, int start, int end, int target) {
    if (start > end) {
        return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] == target) {
        return mid;
    } else if (nums[mid] > target) {
        return binearySearch3(nums, start, mid - 1, target);
    } else {
        return binearySearch3(nums, mid + 1, end, target);
    }
}

int main() {
    vector<int> nums   = { 13, 21, 33, 37, 40, 48, 50, 51, 69, 73, 82 };
    int         target = 50;
    cout << binearySearch1(nums, target) << endl;
    cout << binearySearch2(nums, target) << endl;
    cout << binearySearch3(nums, 0, nums.size() - 1, target) << endl;
}