/**
 * @file Builder.hpp
 * @brief 建造者模式
 * @author Leaos
 * @date 2022-10-25
 */

#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <string>
using namespace std;

/// @brief 产品类
class Proudct {
public:
    Product() = default;

    string getPartA() const { return partA; }
    void   setPartA(const string& part) { partA = part; }
    string getPartB() const { return partB; }
    void   setPartB(const string& part) { partB = part; }
    string getPartC() const { return partB; }
    void   setPartC(const string& part) { partB = part; }

private:
    string partA;
    string partB;
    string partC;
};

/// @brief 抽象建造者
class Builder {
public:
    Builder()
        : prod(new Product) { }
    virtual void buildA() = 0;
    virtual void buildB() = 0;
    virtual void buildC() = 0;

    Product* getProduct() const { return prod; }

protected:
    Product* prod;
};

/// @brief 具体建造者A
class BuilderA : public Builder {
public:
    BuilderA() = default;
    virtual void buildA() override;
    virtual void buildB() override;
    virtual void buildC() override;
};

/// @brief 具体建造者B
class BuilderB : public Builder {
public:
    BuilderB() = default;
    virtual void buildA() override;
    virtual void buildB() override;
    virtual void buildC() override;
};

/// @brief 指挥者类
class Director {
public:
    Director(Builder* build)
        : builder(build) { }
    void     setBuilder(Builder* build) { builder = build; }
    Proudct* construct();

private:
    Builder* builder;
};
#endif // !_BUILDER_H_