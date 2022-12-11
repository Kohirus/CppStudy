/**
 * @file Visitor.hpp
 * @brief 访问者模式的实现
 * @author Leaos
 * @date 2022-12-11
 */

#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <vector>
using namespace std;

/// @brief 抽象访问者类
class Visitor {
public:
    Visitor()                                      = default;
    virtual void visit(ConcreteElementA* elementA) = 0;
    virtual void visit(ConcreteElementB* elementB) = 0;
};

/// @brief 具体访问者类
class ConcreteVisitor : public Visitor {
public:
    ConcreteVisitor() = default;
    virtual void visit(ConcreteElementA* elementA) override;
    virtual void visit(ConcreteElementB* elementB) override;
};

/// @brief 抽象元素类
class Element {
public:
    Element()                             = default;
    virtual void accept(Visitor* visitor) = 0;
};

/// @brief 具体元素A类
class ConcreteElementA : public Element {
public:
    ConcreteElementA() = default;
    virtual void accept(Visitor* visitor);

    void operationA();
};

/// @brief 具体元素A类
class ConcreteElementB : public Element {
public:
    ConcreteElementB() = default;
    virtual void accept(Visitor* visitor);

    void operationB();
};

/// @brief 对象结构类
class ObjectStructure {
public:
    // 接受访问者的访问操作
    void accept(Visitor* visitor);

    void addElement(Element* element);

    void removeElement(Element* element);

private:
    vector<Element*> vec;
};

#endif // !_VISITOR_H_