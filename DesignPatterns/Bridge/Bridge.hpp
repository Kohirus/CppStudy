/**
 * @file Bridge.hpp
 * @brief 桥接模式
 * @author Leaos
 * @date 2022-10-27
 */

#ifndef _BRIDGE_H_
#define _BRIDGE_H_

/// @brief 抽象类
class Abstract {
public:
    virtual void operator() = 0;

    void setImplementor(Implementor* impl) { this->impl = impl; }

protected:
    Implementor* impl;
};

/// @brief 扩充抽象类
class RefinedAbstraction : public Abstract {
public:
    virtual void operator() override;
};

/// @brief 抽象实现类
class Implementor {
public:
    virtual void operatorImpl() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    virtual void operatorImpl() override;
};

class ConcreteImplementorB : public Implementor {
public:
    virtual void operatorImpl() override;
};

#endif // !_BRIDGE_H_
