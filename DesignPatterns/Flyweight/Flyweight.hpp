/**
 * @file Flyweight.hpp
 * @brief 享元模式
 * @author Leaos
 * @date 2022-11-1
 */

#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

#include <map>
#include <string>

/// @brief 外部状态类
class ExternalState {
public:
    ExternalState() = default;
    void operation();
};

/// @brief 抽象享元类
class Flyweight {
public:
    Flyweight() = default;
    void        operation(const ExternalState& outState);
    virtual int dosomething() = 0;
};

/// @brief 具体享元类A
class ConcreteFlyweightA : public Flyweight {
public:
    ConcreteFlyweightA() = default;
    virtual int dosomething() override;
};

/// @brief 具体享元类B
class ConcreteFlyweightB : public Flyweight {
public:
    ConcreteFlyweightB() = default;
    virtual int dosomething() override;
};

/// @brief 单例模式实现的享元工厂类
class FlyweightFactory {
public:
    typedef std::map<std::string, Flyweight*> HashTable;

    static FlyweightFactory& getInstance();
    static Flyweight*        getValue(const std::string& key);

private:
    FlyweightFactory();
    FlyweightFactory(const FlyweightFactory&)            = delete;
    FlyweightFactory& operator=(const FlyweightFactory&) = delete;

private:
    static HashTable _hash;
};

#endif // !_FLYWEIGHT_H_