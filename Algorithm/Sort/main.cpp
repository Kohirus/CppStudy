#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "sort.hpp"
using namespace std;

const int VEC_LEN = 100000; // 随机数组的长度
const int VAL_MIN = 0;      // 数组元素的最小值
const int VAL_MAX = 10000;  // 数组元素的最大值

void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

// 生成随机数组
vector<int> createRandomVector() {
    vector<int> res(VEC_LEN, 0);
    for (int i = 0; i < res.size(); i++) {
        res[i] = (rand() % (VAL_MAX - VAL_MIN + 1)) + VAL_MIN;
    }
}

int main() {
    srand((unsigned)time(NULL));
    vector<int> smallNums = { 18, 54, 26, 2, 67, 99, 72, 46, 81, 11 };
    vector<int> largeNums = createRandomVector();

    // ==========================================================
    // 冒泡排序
    cout << ">>> Bubble Sort: " << endl;
    cout << "Small Vector: ";
    vector<int> bsSmallNums = smallNums, bsLargeNums = largeNums;
    bubbleSort(bsSmallNums);
    printVector(bsSmallNums);
    auto start = std::chrono::steady_clock::now();
    bubbleSort(bsLargeNums);
    auto end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    std::chrono::duration<double> elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
    // ==========================================================

    // ==========================================================
    // 快速排序
    cout << "=======================================" << endl;
    cout << ">>> Selection Sort: " << endl;
    cout << "Small Vector: ";
    vector<int> ssSmallNums = smallNums, ssLargeNums = largeNums;
    selectionSort(ssSmallNums);
    printVector(ssSmallNums);
    start = std::chrono::steady_clock::now();
    selectionSort(ssLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
    // ==========================================================

    return 0;
}