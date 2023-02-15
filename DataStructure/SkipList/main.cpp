#include "skiplist.hpp"
#include <iostream>
using namespace std;

int main() {
    SkipList list;
    for (int i = 1; i <= 20; i++) {
        list.add(i);
    }
    list.print();
    cout << "============================" << endl;
    if (list.find(8)) {
        cout << "exist!" << endl;
    } else {
        cout << "no exist!" << endl;
    }

    if (list.find(30)) {
        cout << "exist!" << endl;
    } else {
        cout << "no exist!" << endl;
    }
    cout << "============================" << endl;
    list.remove(10);
    list.remove(19);
    list.print();
    return 0;
}