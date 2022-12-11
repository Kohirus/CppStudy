#include "Visitor.hpp"
#include <iostream>
using namespace std;

void ConcreteVisitor::visit(ConcreteElementA* element) {
    cout << "ConcreteVisitor::visit(ConcreteElementA*)" << endl;
}

void ConcreteVisitor::visit(ConcreteElementB* element) {
    cout << "ConcreteVisitor::visit(ConcreteElementB*)" << endl;
}

void ConcreteElementA::accept(Visitor* visitor) {
    visitor->visit(this);
}

void ConcreteElementA::operationA() {
    cout << "ConcreteElementA::operationA()" << endl;
}

void ConcreteElementB::accept(Visitor* visitor) {
    visitor->visit(this);
}

void ConcreteElementB::operationB() {
    cout << "ConcreteElementB::operationB()" << endl;
}

void ObjectStructure::accept(Visitor* visitor) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i]->accept(visiotr);
    }
}

void ObjectStructure::addElement(Element* element) {
    vec.push_back(element);
}

void ObjectStructure::removeElement(Element* element) {
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        if (*iter == element) {
            iter = vec.erase(iter);
        }
    }
}