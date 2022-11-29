/**
 * @file Interpreter.hpp
 * @brief 解释器模式
 * @author Leaos
 * @date 2022-11-29
 */

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <map>
#include <string>

using namespace std;

/// @brief 环境类
class Context {
    Context() = default;
    // 添加新值
    void assign(const string& key, const string& value);
    // 获取相应的值
    string lookup(const string& key);

private:
    map<string, string> hash;
};

/// @brief 抽象表达式类
class AbstractExpression {
public:
    AbstractExpression()                 = default;
    virtual void interpret(Context& ctx) = 0;
};

/// @brief 终结表达式
class TerminalExpression : public AbstractExpression {
public:
    TerminalExpression() = default;
    // 解释终结符表达式
    void interpret(Context& ctx);
};

/// @brief 非终结表达式
class NoterminalExpression : public AbstractExpression {
public:
    NoterminalExpression(AbstractExpression* left, AbstractExpression* right);
    // 解释非终结符表达式
    void interpret(Context& ctx);

private:
    AbstractExpression* _left;
    AbstractExpression* _right;
};

#endif // !_INTERPRETER_H_