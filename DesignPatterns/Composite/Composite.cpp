#include "Composite.hpp"
#include <iostream>
using namespace std;

void Transparent::Leaf::add(Transparent::Component* c) {
    cout << "Can't add! Throw exception!" << endl;
}

void Transparent::Leaf::remove(Transparent::Component* c) {
    cout << "Can't remove! Throw exception!" << endl;
}

Transparent::Component* Transparent::Leaf::getChild(int idx) {
    cout << "Can't get child! Throw exception" << endl;
}

void Transparent::Leaf::operation() {
    cout << "do some operation" << endl;
}

void Transparent::Composite::add(Transparent::Component* c) {
    vec.push_back(c);
}

void Transparent::Composite::remove(Transparent::Component* c) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (*iter == c) {
            iter = vec.erase(iter);
        }
    }
}

Transparent::Component* Transparent::Composite::getChild(int idx) {
    return vec.at(idx);
}

void Transparent::Composite::operation() {
    cout << "do some operation" << endl;
}

void Security::Leaf::operation() {
    cout << "do some operation" << endl;
}

void Security::Composite::add(Security::Component* c) {
    vec.push_back(c);
}

void Security::Composite::remove(Security::Component* c) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (*iter == c) {
            iter = vec.erase(iter);
        }
    }
}

Security::Component* Security::Composite::getChild(int idx) {
    return vec.at(idx);
}

void Security::Composite::operation() {
    cout << "do some operation" << endl;
}