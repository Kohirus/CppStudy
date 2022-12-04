/**
 * @file State.hpp
 * @brief 状态模式的实现
 * @author Leaos
 * @date 2022-12-04
 */

#ifndef _STATE_H_
#define _STATE_H_

/// @brief 抽象状态类
class State {
public:
    State() = default;
    // 声明抽象业务方法 不同的具体状态类可以以不同的方法实现
    virtual void handle() = 0;
};

/// @brief 具体状态A类
class ConcreteStateA : public State {
public:
    ConcreteStateA() = default;
    virtual void handle() override;
};

/// @brief 具体状态B类
class ConcreteStateB : public State {
public:
    ConcreteStateB() = default;
    virtual void handle() override;
};

/// @brief 环境类
class Context {
public:
    Context() = default;
    // 设置对象状态
    void setState(State* st) { state = st; }
    void changeState();
    void request();

private:
    State* state; // 维持一个对抽象状态对象的引用
    int    value; // 其他属性值 该属性值的变化可能会导致对象状态发生变化
};

#endif // !_STATE_H_