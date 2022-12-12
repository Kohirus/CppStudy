#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "array.hpp"
using namespace std;

void print(const Array& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.at(i) << " ";
    }
    cout << endl;
}

int main() {
    Array arr;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100);
    }
    print(arr);
    arr.push_back(rand() % 100);
    arr.push_back(rand() % 100);
    arr.push_back(rand() % 100);
    print(arr);
    arr.pop_back();
    arr.pop_back();
    print(arr);
    arr.insert(4, rand() % 100);
    print(arr);
    arr.erase(6);
    print(arr);
    int idx = arr.find(10);
    cout << idx;
    return 0;
}