/**
 * @file Composite.hpp
 * @brief 组合模式
 * @author Leaos
 * @date 2022-10-28
 */

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <vector>
using namespace std;

/// @brief 透明组合模式
namespace Transparent {

/// @brief 抽象构件类
class Component {
public:
    virtual void add(Component*) = 0;

    virtual void remove(Component*) = 0;

    virtual Component* getChild(int idx) = 0;

    virtual void operation() = 0;
};

/// @brief 叶子构件
class Leaf : public Component {
public:
    virtual void add(Component*) override;

    virtual void remove(Component*) override;

    virtual Component* getChild(int idx) const override;

    virtual void operation() override;
};

/// @brief 容器构件
class Composite : public Component {
public:
    virtual void add(Component*) override;

    virtual void remove(Component*) override;

    virtual Component* getChild(int idx) const override;

    virtual void operation() override;

protected:
    vector<Component*> vec;
};

};

/// @brief 安全组合模式
namespace Security {

/// @brief 抽象构件类
class Component {
public:
    virtual void operation() = 0;
};

/// @brief 叶子构件
class Leaf : public Component {
public:
    virtual void operation() override;
};

/// @brief 容器构件
class Composite : public Component {
public:
    virtual void add(Component*);

    virtual void remove(Component*);

    virtual Component* getChild(int idx) const;

    virtual void operation() override;

protected:
    vector<Component*> vec;
};

};

#endif // !_COMPONENT_H_