#include "Bridge.hpp"
#include <iostream>

void RefinedAbstraction::operator() {
    impl->operatorImpl();
}

void ConcreteImplementorA::operatorImpl() {
    cout << "operator A impl" << endl;
}

void ConcreteImplementorB::operatorImpl() {
    cout << "operator B impl" << endl;
}