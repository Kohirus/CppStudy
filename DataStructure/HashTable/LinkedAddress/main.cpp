#include <iostream>
#include "hash.hpp"
using namespace std;

int main() {
    HashTable hash;
    hash.insert(15);
    hash.insert(25);
    hash.insert(7);
    hash.insert(22);
    hash.insert(37);
    hash.print();
    hash.insert(5);
    hash.insert(33);
    hash.print();
    hash.insert(5);
    hash.print();
    cout << hash.find(5) << endl;
    hash.remove(5);
    cout << hash.find(5) << endl;
    hash.remove(7);
    hash.remove(22);
    hash.print();
    return 0;
}