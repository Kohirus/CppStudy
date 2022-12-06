#include "Strategy.hpp"
#include <iostream>
using namespace std;

void ConcreteStrategyA::algorithm() {
    cout << "Bubble Sort" << endl;
}

void ConcreteStrategyB::algorithm() {
    cout << "Quick Sort" << endl;
}

Context::Context(AbstractStrategy* s)
    : strategy(strategy) {
}

void Context::algorithm() {
    strategy->algorithm();
}
