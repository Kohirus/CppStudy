/**
 * @file FactoryMethod.h
 * @brief 工厂方法模式
 * @author Leaos
 * @date 2022-10-22
 */

#ifndef _FACTORY_METHOD_H_
#define _FACTORY_METHOD_H_

/// @brief 抽象产品基类
class BaseProduct {
public:
    BaseProduct()       = default;
    virtual void func() = 0;
};

/// @brief 产品A类
class ProductA : public BaseProduct {
public:
    ProductA() = default;
    virtual void func() override;
};

/// @brief 产品B类
class ProductB : public BaseProduct {
public:
    ProductB() = default;
    virtual void func() override;
};

/// @brief 抽象工厂基类
class BaseFactory {
public:
    BaseFactory()                    = default;
    virtual Product* createProduct() = 0;
};

/// @brief 工厂A类
class FactoryA : public BaseFactory {
public:
    FactoryA() = default;
    virtual BaseProduct* createProduct() override;
};

/// @brief 工厂B类
class FactoryB : public BaseFactory {
public:
    FactoryB() = default;
    virtual BaseProduct* createProduct() override;
};

#endif // !_FACTORY_METHOD_H_