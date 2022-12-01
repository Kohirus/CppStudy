/**
 * @file Mediator.hpp
 * @brief 中介者模式
 * @author Leaos
 * @date 2022-12-01
 */

#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

/// @brief 抽象中介者
class Mediator {
public:
    Mediator() = default;
    // 注册方法 用于增加同事对象
    void register(Colleague* colleague);
    // 声明抽象的业务方法
    virtual void operation() = 0;

protected:
    vector<Colleague*> colleagues;
};

/// @brief 具体中介者
class ConcreteMediator : public Mediator {
public:
    ConcreteMediator() = default;
    // 实现业务方法 封装同事之间的调用
    virtual void operation() override;
};

/// @brief 抽象同事类
class Colleague {
public:
    Colleague(Mediator* media);
    // 声明自身方法 处理自己的行为
    virtual void method1() = 0;
    // 定义依赖方法 与中介者进行通信
    void method2();

protected:
    Mediator* mediator; // 维持一个抽象中介者的引用
};

/// @brief 具体同事类
class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* media);
    // 实现自身方法
    virtual void method1() override;
};

#endif // !_MEDIATOR_H_