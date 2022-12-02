#include "Memento.hpp"

Memento Originator::createMemento() {
    return Memento(this);
}

void Originator::restoreMemento(const Memento& m) {
    state = m.state;
}

Memento::Memento(const Originator& orig)
    : state(orig.state) {
}