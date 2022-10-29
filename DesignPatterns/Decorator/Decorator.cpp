#include "Decorator.hpp"
#include <iostream>
using namesapce std;

void ConcreteComponent::operation() {
    cout << "do some operation" << endl;
}

void Decorator::operation() {
    _component->operation();
}

void ConcreteDecotator::operation() {
    Decorator::operation();
    addedBehavior();
}

void ConcreteDecorator::addedBehavior() {
    cout << "do some behavior" << endl;
}