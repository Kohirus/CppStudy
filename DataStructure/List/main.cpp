#include <iostream>
#include "slist.hpp"
#include "circlelink.hpp"
#include "doublelink.hpp"
#include "doublecirclelink.hpp"
using namespace std;

int main() {
    cout << "Single linked list:" << endl;
    SList list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(3);
    list.push_front(4);
    list.print();
    list.remove(3);
    list.print();
    list.remove(4);
    list.push_back(5);
    list.push_back(5);
    list.push_back(5);
    list.print();
    list.remove(5);
    list.print();
    if (list.find(5))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    if (list.find(4))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    list.push_front(5);
    list.removeAll(5);
    list.print();

    cout << endl
         << "=======================" << endl;
    cout << "Unidirectional loop linked list:" << endl;
    CircleLink link;
    link.push_back(1);
    link.push_back(2);
    link.push_front(3);
    link.push_front(4);
    link.print();
    link.push_back(5);
    link.push_front(5);
    link.print();
    link.remove(5);
    link.print();
    link.remove(5);
    link.print();
    link.remove(3);
    link.print();
    if (link.find(2))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    if (link.find(5))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;

    cout << endl
         << "=======================" << endl;
    cout << "Double linked list:" << endl;
    DoubleLink dlink;
    dlink.push_back(1);
    dlink.push_back(2);
    dlink.push_front(3);
    dlink.push_front(4);
    dlink.print();
    dlink.remove(2);
    dlink.print();
    dlink.remove(4);
    dlink.print();
    dlink.push_back(5);
    dlink.remove(1);
    dlink.print();
    if (dlink.find(5))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    if (dlink.find(4))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;

    cout << endl
         << "=======================" << endl;
    cout << "Double circle linked list:" << endl;
    DoubleCircleLink dclink;
    dclink.push_back(1);
    dclink.push_back(2);
    dclink.push_front(3);
    dclink.push_front(4);
    dclink.print();
    dclink.push_back(5);
    dclink.push_front(5);
    dclink.print();
    dclink.remove(5);
    dclink.remove(5);
    dclink.print();
    dclink.remove(1);
    dclink.print();
    if (dclink.find(3))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    if (dclink.find(5))
        cout << "Exist!" << endl;
    else
        cout << "Not Exist!" << endl;
    return 0;
}