#include "Proxy.hpp"
#include <iostream>

using namespace std;

void RealSubject::request() {
    cout << "RealSubject::request" << endl;
}

void Proxy::preReuqest() {
    cout << "Proxy::preReuqest" << endl;
}

void Proxy::request() {
    cout << "Proxy::request" << endl;
}

void Proxy::postReuqest() {
    cout << "Proxy::postReqest" << endl;
}
