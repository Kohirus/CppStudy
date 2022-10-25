#include "Builder.hpp"
#include <iostream>
using namespace std;

void BuilderA::buildA() {
    cout << "A Builder create Product A" << endl;
}

void BuilderA::buildB() {
    cout << "A Builder create Product B" << endl;
}

void BuilderA::buildC() {
    cout << "A Builder create Product C" << endl;
}

void BuilderB::buildA() {
    cout << "B Builder create Product A" << endl;
}

void BuilderB::buildB() {
    cout << "B Builder create Product B" << endl;
}

void BuilderB::buildC() {
    cout << "B Builder create Product C" << endl;
}

Product* Director::construct() {
    builder->buildA();
    builder->buildB();
    builder->buildC();
    return builer->getProduct();
}
