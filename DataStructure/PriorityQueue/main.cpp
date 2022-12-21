#include <iostream>
#include <functional>
#include "priorityqueue.hpp"
using namespace std;

int main() {
    PriorityQueue que;
    que.push(18);
    que.push(54);
    que.push(26);
    que.push(2);
    que.push(67);
    que.push(99);
    cout << "Large root heap: " << endl;
    while (!que.empty()) {
        cout << "Top: " << que.top() << endl;
        que.pop();
    }

    cout << "============================" << endl;
    cout << "Small root head: " << endl;
    PriorityQueue sque(20, less<int>());
    sque.push(18);
    sque.push(54);
    sque.push(26);
    sque.push(2);
    sque.push(67);
    sque.push(99);
    while (!sque.empty()) {
        cout << "Top: " << sque.top() << endl;
        sque.pop();
    }
}