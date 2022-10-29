/**
 * @file Decorator.hpp
 * @brief 装饰模式
 * @author Leaos
 * @date 2022-10-29
 */

#ifndef _DECORATOR_H_
#define _DECORATOR_H_

/// @brief 抽象构件类
class Component {
public:
    virtual void operation() = 0;
};

/// @brief 具体构件类
class ConcreteComponent : public Component {
public:
    virtual void operation() override;
};

/// @brief 抽象装饰器类
class Decorator {
public:
    Decorator(Component* component)
        : _component(component) { }
    void         setComponent(Component* component) { _component = component; }
    virtual void operation();

private:
    Component* _component;
}

/// @brief 具体装饰器类
class ConcreteDecorator : public Decorator {
public:
    virtual void operation() override;
    virtual void addedBehavior();
};

#endif // !_DECORATOR_H_