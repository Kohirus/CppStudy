#include "Iterator.hpp"

Iterator ConcreteAggregate::createIterator() {
    return ConcreteIterator(this);
}

ConcreteIterator::ConcreteIterator(ConcreteAggregate* obj)
    : objects(obj) { }
