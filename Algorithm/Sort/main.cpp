#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "sort.hpp"
using namespace std;

#define SMALL_TEST // 开启小数据测试
#define LARGE_TEST // 开启大数据测试

#define BUBBLE_SORT    // 开启冒泡排序
#define SELECTION_SORT // 开启选择排序
#define INSERTION_SORT // 开启插入排序
#define SHELL_SORT     // 开启希尔排序
#define QUICK_SORT     // 开启快速排序
#define MERGE_SORT     // 开启归并排序
#define HEAP_SORT      // 开启堆排序

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
    vector<int>                   smallNums = { 18, 54, 26, 2, 67, 99, 72, 46, 81, 11 };
    vector<int>                   largeNums = createRandomVector();
    auto                          start = std::chrono::steady_clock::now(), end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed;

#ifdef BUBBLE_SORT
    // ==========================================================
    // 冒泡排序
    cout << "=======================================" << endl;
    cout << ">>> Bubble Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> bsSmallNums = smallNums;
    bubbleSort(bsSmallNums);
    printVector(bsSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> bsLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    bubbleSort(bsLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // BUBBLE_SORT

#ifdef SELECTION_SORT
    // ==========================================================
    // 快速排序
    cout << "=======================================" << endl;
    cout << ">>> Selection Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> ssSmallNums = smallNums;
    selectionSort(ssSmallNums);
    printVector(ssSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> ssLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    selectionSort(ssLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // SELECTION_SORT

#ifdef INSERTION_SORT
    // ==========================================================
    // 插入排序
    cout << "=======================================" << endl;
    cout << ">>> Insertion Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> isSmallNums = smallNums;
    insertionSort(isSmallNums);
    printVector(isSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> isLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    insertionSort(isLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // INSERTION_SORT

#ifdef SHELL_SORT
    // ==========================================================
    // 希尔排序
    cout << "=======================================" << endl;
    cout << ">>> Shell Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> shsSmallNums = smallNums;
    shellSort(shsSmallNums);
    printVector(shsSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> shsLargeNums = largeNums;
    start                    = std::chrono::steady_clock::now();
    shellSort(shsLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // SHELL_SORT

#ifdef QUICK_SORT
    // ==========================================================
    // 快速排序
    cout << "=======================================" << endl;
    cout << ">>> Quick Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> qsSmallNums = smallNums;
    quickSort(qsSmallNums);
    printVector(qsSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> qsLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    quickSort(qsLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // QUICK_SORT

#ifdef MERGE_SORT
    // ==========================================================
    // 归并排序
    cout << "=======================================" << endl;
    cout << ">>> Merge Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> msSmallNums = smallNums;
    mergeSort(msSmallNums);
    printVector(msSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> msLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    mergeSort(msLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // MERGE_SORT

#ifdef HEAP_SORT
    // ==========================================================
    // 堆排序
    cout << "=======================================" << endl;
    cout << ">>> Heap Sort: " << endl;

#ifdef SMALL_TEST
    cout << "Small Vector: ";
    vector<int> hsSmallNums = smallNums;
    heapSort(hsSmallNums);
    printVector(hsSmallNums);
#endif // SMALL_TEST

#ifdef LARGE_TEST
    vector<int> hsLargeNums = largeNums;
    start                   = std::chrono::steady_clock::now();
    heapSort(hsLargeNums);
    end = std::chrono::steady_clock::now();
    cout << "Large Vector: ";
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << elapsed.count() << " seconds" << endl;
#endif // LARGE_TEST

    // ==========================================================
#endif // HEAP_SORT

    return 0;
}