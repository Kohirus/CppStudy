#include "Adapter.hpp"

void ObjectAdapter::request() {
    adaptee.specificRequest();
}

void ClassAdapter::request() {
    this->request();
}