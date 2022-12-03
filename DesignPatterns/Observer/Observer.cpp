#include "Observer.hpp"
#include <iostream>
using namespace std;

void ConcreteObserver::update() {
    cout << "call update()" << endl;
}

void Subject::attach(Observer* obs) {
    observers.push_back(obs);
}

void Subject::detach(Observer* obs) {
    for (auto iter = observers.begin(); iter != observers.end(); ++iter) {
        if (*iter == obs) {
            observers.erase(iter);
            break;
        }
    }
}

void ConcreteSubject::notify() {
    // 遍历观察者集合 调用每一个观察者的响应方法
    for (auto obs : observers) {
        obs->update();
    }
}