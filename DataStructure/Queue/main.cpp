#include <iostream>
#include "circlequeue.hpp"
#include "linkedqueue.hpp"
using namespace std;

int main() {
    cout << "Circle Queue:" << endl;
    CircleQueue cq;
    cq.push(1);
    cq.push(2);
    cq.push(3);
    cq.push(4);
    cq.push(5);
    cq.print();
    cq.pop();
    cq.print();
    cout << "Head: " << cq.front() << endl;
    cout << "Tail: " << cq.back() << endl;
    if (cq.empty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Queue is not empty" << endl;
    }

    cout << endl;
    cout << "======================" << endl;
    cout << "Linked Queue:" << endl;
    LinkedQueue lq;
    lq.push(1);
    lq.push(2);
    lq.push(3);
    lq.push(4);
    lq.push(5);
    lq.print();
    lq.pop();
    lq.pop();
    lq.print();
    cout << "Head: " << lq.front() << endl;
    cout << "Tail: " << lq.back() << endl;
    if (lq.empty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Queue is not empty" << endl;
    }
    return 0;
}