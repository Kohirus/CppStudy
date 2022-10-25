/**
 * @file Prototype.hpp
 * @brief 原型模式
 * @author Leaos
 * @date 2022-10-24
 */

#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

#include <string>
#include <map>
using namespace std;

/// @brief 抽象原型类
class Prototype {
public:
    Prototype()                 = default;
    Prototype(const Prototype&) = default;
    virtual Prototype* clone()  = 0;
};

/// @brief 具体原型类A
class ConcretePrototypeA : public Prototype {
public:
    ConcretePrototypeA()
        : _ptr(nullptr)
        , _str("") { }
    ConcretePrototypeA(const ConcretePrototypeA&);
    ConcretePrototypeA& operator=(const ConcretePrototypeA&);
    ~ConcretePrototypeA();
    virtual Prototype* clone() override;

    void   setPtr(int* p) { _ptr = p; }
    int*   getPtr() const { return _ptr; }
    void   setString(const string& str) { _str = str; }
    string getString() const { return _str; }

private:
    int*   _ptr;
    string _str;
};

/// @brief 具体原型类B
class ConcretePrototypeB : public Prototype {
public:
    ConcretePrototypeB()
        : _ptr(nullptr)
        , _str("") { }
    ConcretePrototypeB() = default;
    ConcretePrototypeB(const ConcretePrototypeB&);
    ConcretePrototypeB& operator=(const ConcretePrototypeB&);
    ~ConcretePrototypeB();
    virtual Prototype* clone() override;

    void   setPtr(char* p) { _ptr = p; }
    char*  getPtr() const { return _ptr; }
    void   setString(const string& str) { _str = str; }
    string getString() const { return _str; }

private:
    char* _ptr;
    int   _num;
};

/// @brief 单例模式实现的原型管理器
class PrototypeManager {
public:
    typedef map<string, Prototype*> PrototypeMap;
    static PrototypeManager*        getInstance() {
               static PrototypeManager instance;
               return &instance;
    }

    void       addItem(const string& name, Prototype* prototype);
    Prototype* getItem(const string& name) const;

private:
    PrototypeManager() = default;

    PrototypeMap _hash;
};

#endif // !_PROTOTYPE_H_