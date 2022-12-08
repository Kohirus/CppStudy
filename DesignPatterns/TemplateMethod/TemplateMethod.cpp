#include "TemplateMethod.hpp"
#include <iostream>
using namespace std;

void AbstractClass::templateMethod() {
    primitiveOperation1();
    primitiveOperation2();
    primitiveOperation3();
}

void AbstractClass::primitiveOperation1() {
    cout << "call primitiveOperation1" << endl;
}

void AbstractClass::primitiveOperation3() {
    cout << "call AbstractClass::primitiveOperation3" << endl;
}

void ConcreteClass::primitiveOperation2() {
    cout << "call ConcreteClass::primitiveOperation2" << endl;
}

void ConcreteClass::primitiveOperation3() {
    cout << "call ConcreteClass::primitiveOperation3" << endl;
}