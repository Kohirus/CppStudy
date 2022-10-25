/**
 * @file AbstractFactory.hpp
 * @brief 抽象工厂模式
 * @author Leaos
 * @date 2022-10-23
 */

#ifndef _ABSTRACT_FACTORY_H_
#define _ABSTRACT_FACTORY_H_

/// @brief 抽象产品A
class AbstractProudctA {
public:
    AbstractProudctA()   = default;
    virtual void funcA() = 0;
};

/// @brief 抽象产品B
class AbstractProudctB {
public:
    AbstractProudctB()   = default;
    virtual void funcB() = 0;
};

/// @brief 具体产品A1
class ConcreteProductA1 : public AbstractProudctA {
public:
    ConcreteProductA1() = default;
    virtual void funcA() override;
};

/// @brief 具体产品A2
class ConcreteProductA2 : public ConcreteProudctA {
public:
    ConcreteProductA2() = default;
    virtual void funcA() override;
};

/// @brief 具体产品B1
class ConcreteProductB1 : public AbstractProudctB {
public:
    ConcreteProductB1() = default;
    virtual void funcB() override;
};

/// @brief 具体产品B2
class ConcreteProductB2 : public ConcreteProudctB {
public:
    ConcreteProductB2() = default;
    virtual void funcB() override;
};

/// @brief 抽象工厂类
class AbstractFactory {
public:
    AbstractFactory()                          = default;
    virtual AbstractProudctA* createProductA() = 0;
    virtual AbstractProudctB* createProductB() = 0;
};

/// @brief 具体工厂1
class ConcreteFactory1 : public AbstractFactory {
public:
    ConcreteFactory1() = default;
    virtual AbstractProudctA* createProductA() override;
    virtual AbstractProudctB* createProductB() override;
};

/// @brief 具体工厂2
class ConcreteFactory2 : public AbstractFactory {
public:
    ConcreteFactory2() = default;
    virtual AbstractProudctA* createProductA() override;
    virtual AbstractProudctB* createProductB() override;
};

#endif // !_ABSTRACT_FACTORY_H_
