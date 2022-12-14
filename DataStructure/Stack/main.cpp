#include <iostream>
#include "sequencestack.hpp"
#include "linkedstack.hpp"

using namespace std;

int main() {
    cout << "Sequence Stack:" << endl;
    SequenceStack sst;
    sst.push(1);
    sst.push(2);
    sst.push(3);
    sst.push(4);
    sst.print();
    sst.pop();
    sst.pop();
    sst.print();
    cout << "top = " << sst.top() << endl;
    cout << "size = " << sst.size() << endl;
    cout << "empty? " << sst.empty() << endl;
    sst.pop();
    sst.pop();
    cout << "size = " << sst.size() << endl;
    cout << "empty? " << sst.empty() << endl;

    cout << endl;
    cout << "===========================" << endl;
    cout << "Linked Stack:" << endl;
    LinkedStack lst;
    lst.push(1);
    lst.push(2);
    lst.push(3);
    lst.push(4);
    lst.print();
    lst.pop();
    lst.pop();
    lst.print();
    cout << "top = " << lst.top() << endl;
    cout << "size = " << lst.size() << endl;
    cout << "empty? " << lst.empty() << endl;
    lst.pop();
    lst.pop();
    cout << "size = " << lst.size() << endl;
    cout << "empty? " << lst.empty() << endl;
    return 0;
}