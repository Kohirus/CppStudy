/**
 * @file bitmap.cpp
 * @brief 位图的实现
 * @author Leaos
 * @date 2023-01-07
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

int main() {
    vector<int> vec { 12, 78, 90, 78, 123, 8, 9, 90 };

    // 定义位图数组
    int max = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max)
            max = vec[i];
    }

    int*            bitmap = new int[max / 32 + 1]();
    unique_ptr<int> ptr(bitmap);

    // 找第一个重复出现的数字
    for (auto key : vec) {
        int index  = key / 32;
        int offset = key % 32;

        // 取key对应的位的值
        if (0 == (bitmap[index] & (1 << offset))) {
            // 表示key没有出现过
            bitmap[index] |= (1 << offset);
        } else {
            cout << "Duplicate Number: " << key << endl;
        }
    }
}