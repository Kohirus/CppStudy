#include "Facade.hpp"

void SubSystemA::methodA() {
    _num = 10;
}

void SubSystemB::methodB() {
    _str = "hello world";
}

void SubSystemC::methodC() {
    _ptr = new char;
}

void Facade::interface() {
    _sysA.methodA();
    _sysB.methodB();
    _sysC.methodC();
}