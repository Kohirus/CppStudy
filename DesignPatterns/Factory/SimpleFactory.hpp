/**
 * @file SimpleFactory.hpp
 * @brief 简单工厂模式
 * @author Leaos
 * @date 2022-10-21
 */

#ifndef _SIMPLE_FACTORY_H_
#define _SIMPLE_FACTORY_H_

/// @brief 产品类型
enum ProdcutType {
    ProductA = 0,
    ProductB
};

/// @brief 纯虚基类 产品类
class BaseProduct {
public:
    BaseProduct()       = default;
    virtual void func() = 0;
};

/// @brief 产品A
class ProductA : public BaseProduct {
public:
    ProductA() = default;
    virtual void func() override;
};

/// @brief 产品B
class ProductB : public BaseProduct {
public:
    ProductB() = default;
    virtual void func() override;
};

/// @brief 简单工厂类
class SimpleFactory {
public:
    SimpleFactory() = default;
    static Prodcut* getProduct(ProdcutType type) {
        Prodcut* prodcut = nullptr;
        switch (type) {
        case ProdcutType::ProductA:
            product = new ProductA;
            // initialize ProductA
            break;
        case ProdcutType::ProductB:
            product = new ProductB;
            // initialize ProductB
            break;
        default:
            break;
        }
        return prodcut;
    }
};
#endif // !_SIMPLE_FACTORY_H_