#include "Mediator.hpp"
#include <iostream>

using namespace std;

void Mediator::register(Colleague* colleague) {
    colleagues.push_back(colleague);
}

void ConcreteMediator::operation() {
    colleagues[0].method1();
}

Colleague::Colleague(Mediator* media)
    : mediator(media) {
}

void Colleague::method2() {
    mediator->operation();
}

ConcreteColleague::ConcreteColleague(Mediator* media)
    : Colleague(media) {
}

void ConcreteColleague::method1() {
    cout << "call method1" << endl;
}