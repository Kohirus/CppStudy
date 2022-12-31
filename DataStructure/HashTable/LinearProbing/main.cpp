#include <iostream>
#include "hash.hpp"
using namespace std;

int main() {
    HashTable hash;
    hash.insert(12);
    hash.insert(22);
    hash.insert(47);
    hash.insert(29);
    hash.print();
    hash.insert(30);
    hash.insert(66);
    hash.print();
    cout << hash.find(12) << endl;
    hash.erase(12);
    hash.print();
    cout << hash.find(12) << endl;
    hash.erase(22);
    hash.erase(66);
    hash.print();
    return 0;
}