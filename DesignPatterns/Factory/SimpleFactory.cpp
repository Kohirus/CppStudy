#include "SimpleFactory.h"
#include <iostream>
using namespace std;

void ProductA::func() {
    cout << "config ProductA" << endl;
}

void ProductB::func() {
    cout << "config ProductB" << endl;
}