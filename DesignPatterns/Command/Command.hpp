#ifndef _COMMAND_H_
#define _COMMAND_H_

/// @brief 抽象命令类
class Command {
public:
    Command()              = default;
    virtual void execute() = 0;
};

/// @brief 接收者 实现具体的业务请求
class Receiver {
public:
    Receiver() = default;
    void action();
};

/// @brief 调用者 即请求发送者
class Invoker {
public:
    Invoker(Command* cmd);

    void setCommand(Command* cmd) { command = cmd; }

    // 业务方法 用于调用命令类的 execute() 方法
    void call();

private:
    Command* command;
};

/// @brief 具体命令类
class ConcreteCommand : public Command {
public:
    ConcreteCommand() = default;
    virtual void execute() override;

private:
    Receiver receiver;
};

#endif // !_COMMAND_H_