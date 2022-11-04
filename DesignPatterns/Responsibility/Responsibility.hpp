/**
 * @file Responsibility.hpp
 * @brief 职责链模式
 * @author Leaos
 * @date 2022-11-4
 */

#ifndef _RESPONSIBILITY_H_
#define _RESPONSIBILITY_H_

#include <string>
#include <vector>
using namespace std;

/// @brief 处理对象
class Object {
public:
    Object() = default;

    void        setName(const string& str) { name = str; }
    string      getName() const { return name; }
    void        setArr(const vector<int>& vec) { arr = vec; }
    vector<int> getArr() const { return arr; }

private:
    vector<int> arr;
    string      name;
}

/// @brief 抽象处理者
class Handler {
public:
    Handler() = default;

    virtual void handleReuqest(Object* obj) = 0;

    void setHandler(Handler* handler) { successor = handler; }

protected:
    Handler* successor;
};

/// @brief 具体处理者A
class HandlerA : public Handler {
public:
    HandlerA() = default;
    virtual void handleRequest(Object* obj) override;
};

/// @brief 具体处理者B
class HandlerB : public Handler {
public:
    HandlerB() = default;
    virtual void handleRequest(Object* obj) override;
};

#endif // !_RESPONSIBILITY_H_