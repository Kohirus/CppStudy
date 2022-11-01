#include "Flyweight.hpp"
#include <iostream>
using namespace std;

void ExternalState::operation() {
    cout << "ExternalState::operation()" << endl;
}

void Flyweight::operation(const ExternalState& outState) {
    outState.operation();
}

int ConcreteFlyweightA::dosomething() {
    return 1;
}

int ConcreteFlyweightB::dosomething() {
    return 2;
}

FlyweightFactory::HashTable FlyweightFactory::_hash;

FlyweightFactory::FlyweightFactory() {
    Flyweight* flyweightA = new ConcreteFlyweightA();
    _hash["A"]            = flyweightA;
    Flyweight* flyweightB = new ConcreteFlyweightB();
    _hash["B"]            = flyweightB;
}

FlyweightFactory& FlyweightFactory::getInstance() {
    static FlyweightFactory instance;
    return instance;
}

Flyweight* FlyweightFactory::getValue(const std::string& key) {
    auto it = _hash.find(key);
    if (it == _hash.end()) {
        return nullptr;
    }
    return it->second;
}