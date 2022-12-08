/**
 * @file TemplateMethod.hpp
 * @brief 模板方法模式的实现
 * @author Leaos
 * @date 2022-12-08
 */

#ifndef _TEMPLATE_METHOD_H_
#define _TEMPLATE_METHOD_H_

/// @brief 抽象模板类
class AbstractClass {
public:
    AbstractClass() = default;

    // 模板方法
    void templateMethod();

    // 基本方法 - 具体方法
    void primitiveOperation1();

    // 基本方法 - 抽象方法
    virtual void primitiveOperative2() = 0;

    // 基本方法 - 钩子方法
    virtual void primitiveOperation3() { }
};

/// @brief 具体类
class ConcreteClass : public AbstractClass {
public:
    virtual void primitiveOperation2() override;
    virtual void primitiveOperation3() override;
};

#endif // !_TEMPLATE_METHOD_H_