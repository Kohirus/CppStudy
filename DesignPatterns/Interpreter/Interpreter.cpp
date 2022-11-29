#include "Interpreter.hpp"
#include <iostream>
using namespace std;

void Context::assign(const string& key, const string& value) {
    hash[key] = value;
}

string Context::lookup(const string& key) {
    auto iter = hash.find(key);
    if (iter != hash.end()) {
        return iter->second;
    }
    return "";
}

void TerminalExpression::interpret(Context& ctx) {
    cout << ctx.lookup("+") << endl;
}

NoterminalExpression::NoterminalExpression(AbstractExpression* left, AbstractExpression* right)
    : _left(left)
    , _right(right) {
}

NoterminalExpression::interpreter(Context& ctx) {
    _left->interpret(ctx);
    _right->interpret(ctx);
}
