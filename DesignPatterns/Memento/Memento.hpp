/**
 * @file Memento.hpp
 * @brief 备忘录模式
 * @author Leaos
 * @date 2022-12-02
 */

#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <string>
using namespace std;

class Memento;

/// @brief 原发器类
class Originator {
public:
    Orignator() = default;
    // 创建一个备忘录对象
    Memento createMemento();
    // 根据备忘录对象恢复到原发器状态
    void restoreMemento(const Memento& m);

    void   setState(const string& st) { state = st; }
    string getState() const { return state; }

private:
    string state;
};

/// @brief 备忘录类
class Memento {
public:
    friend class Originator;

    Memento(const Originator& o);

private:
    string state;
};

/// @brief 负责人类
class Caretaker {
public:
    Caretaker() = default;
    Memento getMemento() const { return menento; }
    void    setMemento(const Menento& mem) { memento = mem; }

private:
    Memento memento;
};

#endif // !_MEMENTO_H_