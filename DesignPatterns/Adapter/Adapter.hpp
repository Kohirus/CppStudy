/**
 * @file Adapter.hpp
 * @brief 对象适配器模式和类适配器模式
 * @author Leaos
 * @date 2022-10-26
 */

#ifndef _ADAPTER_H_
#define _ADAPTER_H_

/// @brief 目标抽象类
class Target {
public:
    Target()               = default;
    virtual void request() = 0;
};

/// @brief 适配者类
class Adaptee {
public:
    void specificRequest();
};

/// @brief 适配器类 对象适配器模式
class ObjectAdapter : public Target {
public:
    ObjectAdapter() = default;
    virtual void request() override;

private:
    Adaptee adaptee;
};

/// @brief 适配器类 类适配器模式
class ClassAdapter : public Target, Adaptee {
public:
    ClassAdapter() = default;
    void request();
};

#endif // !_ADAPTER_H_