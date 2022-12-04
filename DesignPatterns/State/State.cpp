#include "State.hpp"
#include <iostream>
using namespace std;

void ConcreteStateA::handle() {
    cout << "State A handle" << endl;
}

void ConcreteStateB::handle() {
    cout << "State B handle" << endl;
}

void Context::changeState() {
    // 根据环境对象中的属性值进行状态转换
    if (ctx.getValue() == 1) {
        ctx.setState(new ConcreteStateA());
    } else if (ctx.getValue() == 2) {
        ctx.setState(new ConcreteStateB());
    }
}

void Context::request() {
    state.handle(); // 调用状态对象的业务方法
}