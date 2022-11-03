/**
 * @file Proxy.hpp
 * @brief 代理模式
 * @author Leaos
 * @date 2022-11-3
 */

#ifndef _PROXY_H_
#define _PROXY_H_

/// @brief 抽象主题角色
class Subject {
public:
    Subject()              = default;
    virtual void request() = 0;
}

/// @brief 真实主题角色
class RealSubject : public Subject {
public:
    RealSubject() = default;
    virtual void request() override;
};

/// @brief 代理主题角色
class Proxy : public Subject {
public:
    void         preReuqest();
    vitrual void request() override;
    void         postReqest();

private:
    RealSubject realSubject;
};

#endif // !_PROXY_H_