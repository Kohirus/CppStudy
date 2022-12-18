#include <vector>
#include <iostream>
#include "binearysearch.hpp"
using namespace std;

int main() {
    vector<int> nums   = { 13, 21, 33, 37, 40, 48, 50, 51, 69, 73, 82 };
    int         target = 50;
    cout << binearySearch1(nums, target) << endl;
    cout << binearySearch2(nums, target) << endl;
    cout << binearySearch3(nums, 0, nums.size() - 1, target) << endl;
}