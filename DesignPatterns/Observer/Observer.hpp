/**
 * @file Observer.hpp
 * @brief 观察者模式
 * @author Leaos
 * @date 2022-12-03
 */

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>
using namespace std;

/// @brief 抽象观察者类
class Observer {
public:
    Observer()            = default;
    virtual void update() = 0;
};

/// @brief 具体观察者类
class ConcreteObserver : public Observer {
public:
    ConcreteObserver() = default;
    virtual void update() override;
};

/// @brief 目标类
class Subject {
public:
    Subject() = default;
    // 注册方法 用于向观察者集合中增加一个观察者
    void attach(Observer* obs);
    // 注销方法 用于在观察者集合中删除一个观察者
    void detach(Observer* obs);
    // 声明抽象通知方法
    virtual void notify() = 0;

protected:
    // 定义一个观察者集合用于存储所有观察者对象
    vector<Observer*> observers;
};

/// @brief 具体目标类
class ConcreteSubject : public Subject {
public:
    ConcreteSubject() = default;
    // 实现通知方法
    virtual void notify() override;
};

#endif // !_OBSERVER_H_