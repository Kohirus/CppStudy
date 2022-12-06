/**
 * @file Strategy.hpp
 * @brief 策略模式的实现
 * @author Leaos
 * @date 2022-12-06
 */

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

/// @brief 抽象策略类
class AbstractStrategy {
public:
    AbstractStrategy() = default;
    // 声明抽象算法
    virtual void algorithm() = 0;
};

/// @brief 具体策略A类
class ConcreteStrategyA : public AbstractStrategy {
public:
    ConcreteStrategyA() = default;
    // 算法的具体实现
    virtual void algorithm() override;
};

/// @brief 具体策略B类
class ConcreteStrategyB : public AbstractStrategy {
public:
    ConcreteStrategyB() = default;
    // 算法的具体实现
    virtual void algorithm() override;
};

/// @brief 环境类
class Context {
public:
    Context() = default;
    Context(AbstractStrategy* s);
    void setStrategy(AbstractStrategy* s) { strategy = s; }
    // 调用策略中的算法
    void algorithm();

private:
    AbstractStrategy* strategy;
};

#endif // !_STRATEGY_H_