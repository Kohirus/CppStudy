#include "FactoryMethod.h"
#include <iostream>
using namespace std;

void ProductA::func() {
    cout << "initialize ProductA" << endl;
}

void ProductB::func() {
    cout << "initialize ProductB" << endl;
}

BaseProduct* FactoryA::createProduct() {
    BaseProduct* product = new ProductA();
    return product;
}

BaseProduct* FactoryB::createProduct() {
    BaseProduct* product = new ProductB();
    return product;
}