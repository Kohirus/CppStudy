#include <iostream>
#include "unionfind.hpp"
using namespace std;

int main() {
    UnionFind set(8);
    set.merge(1, 3);
    set.merge(1, 2);
    set.merge(5, 4);
    set.merge(2, 4);
    set.merge(6, 8);
    set.merge(8, 7);
    set.print();
    cout << endl;
    cout << set.find(3) << endl;
    cout << set.find(4) << endl;
    cout << set.find(7) << endl;
    cout << set.find(6) << endl;
    cout << endl;
    set.print();
    return 0;
}