#include "Prototype.h"

ConcretePrototypeA()::~ConcretePrototypeA() {
    delete _ptr;
}

ConcretePrototypeA::ConcretePrototypeA(const ConcretePrototypeA& obj) {
    this->_ptr    = new int;
    *(this->_ptr) = *(obj._ptr);
    this->_str    = obj._str;
}

ConcretePrototypeA& ConcretePrototypeA::operator=(const ConcretePrototypeA& obj) {
    if (this != &obj) {
        if (!_ptr) _ptr = new int;
        *(_ptr) = *(obj.getPtr());
        _str    = obj.getString();
    }
    return *this;
}

Prototype* ConcretePrototypeA::clone() {
    Prototype* prototype = new ConcretePrototypeA(this);
    return prototype;
}

ConcretePrototypeB()::~ConcretePrototypeB() {
    delete _ptr;
}

ConcretePrototypeB::ConcretePrototypeB(const ConcretePrototypeB& obj) {
    this->_ptr    = new char;
    *(this->_ptr) = *(obj._ptr);
    this->_str    = obj._str;
}

ConcretePrototypeB& ConcretePrototypeB::operator=(const ConcretePrototypeB& obj) {
    if (this != &obj) {
        if (!_ptr) _ptr = new char;
        *(_ptr) = *(obj.getPtr());
        _str    = obj.getString();
    }
    return *this;
}

Prototype* ConcretePrototypeB::clone() {
    Prototype* prototype = new ConcretePrototypeB();
    prototype->setPtr(this->getPtr());
    prototype->setString(this->getString());
    return prototype;
}

void PrototypeManager::addItem(const char* name, Prototype* prototype) {
    _hash[name] = prototype;
}

Prototype* getItem(const string& name) {
    return _hash[name];
}