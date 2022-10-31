/**
 * @file Facade.hpp
 * @brief 外观模式
 * @author Leaos
 * @date 2022-10-31
 */

#ifndef _FACADE_H_
#define _FACADE_H_

#include <string>

/// @brief 子系统A
class SubSystemA {
public:
    SubSystemA() = default;
    void methodA();

private:
    int _num;
};

/// @brief 子系统B
class SubSystemB {
public:
    SubSystemB() = default;
    void methodB();

private:
    string _str;
};

/// @brief 子系统C
class SubSystemC {
public:
    SubSystemC() = default;
    void methodC();

private:
    char* _ptr;
};

/// @brief 外观类
class Facade {
public:
    Facade() = default;
    void interface();

private:
    SubSystemA _sysA;
    SubSystemB _sysB;
    SubSystemC _sysC;
};

#endif // !_FACADE_H_