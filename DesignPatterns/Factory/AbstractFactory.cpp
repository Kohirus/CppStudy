#include "AbstractFactory.h"
#include <iostream>
using namespace std;

void ConcreteProductA1::func() {
    cout << "create Product-A-1" << endl;
}

void ConcreteProductA2::func() {
    cout << "create Product-A-2" << endl;
}

void ConcreteProductB1::func() {
    cout << "create Product-B-1" << endl;
}

void ConcreteProductB2::func() {
    cout << "create Product-B-2" << endl;
}

AbstractProudctA* ConcreteFactory1::createProductA() {
    AbstractProudctA* ptr = new ConcreteProductA1;
    return ptr;
}

AbstractProudctB* ConcreteFactory1::createProductB() {
    AbstractProudctB* ptr = new ConcreteProductB1;
    return ptr;
}

AbstractProudctA* ConcreteFactory2::createProductA() {
    AbstractProudctA* ptr = new ConcreteProductA2;
    return ptr;
}

AbstractProudctB* ConcreteFactory2::createProductB() {
    AbstractProudctB* ptr = new ConcreteProductB2;
    return ptr;
}