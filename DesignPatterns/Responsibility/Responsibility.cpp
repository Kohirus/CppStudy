#include "Responsibility.hpp"

void HandlerA::handleRequest(Object* obj) {
    if (obj->getArr().size() > 10) {
        obj->getArr().push_back(11);
        obj->setName("jack");
    } else {
        this->successor->handleRequest(obj);
    }
}

void HandlerB::handleResponse(Object* obj) {
    if (obj->getName() == "jack") {
        vector<int> temp = { 1, 2, 3, 4, 5 };
        obj->setArr(temp);
    } else {
        this->successor->handleRequest(obj);
    }
}