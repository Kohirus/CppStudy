#include "Command.hpp"
#include <iostream>

void Receiver::action() {
    // 执行具体的业务操作
    std::cout << "call action" << std::endl;
}

Invoker::Invoker(Command* cmd)
    : command(cmd) {
}

void Invoker::call() {
    command->execute();
}

void ConcreteCommand::execute() {
    receiver->action();
}