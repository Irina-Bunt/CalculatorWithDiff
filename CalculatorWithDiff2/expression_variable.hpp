#pragma once
#include "expression_number.hpp"

class Variable final : public Expression
{
public:
    Variable(string ivar) : var(ivar) {};
    shared_ptr<ExpressionInterface> Clone() const override { return shared_ptr<Variable>(new Variable(var)); }
    string ToString() const override { return var; }
    int Calc(const string& s) const override;
    shared_ptr<ExpressionInterface> Diff(const string& v) const override { return shared_ptr<Number>(new Number(var == v ? 1 : 0)); };
    shared_ptr<ExpressionInterface> Simpl() const override { return shared_ptr<Variable>(new Variable(var)); }
    static bool Check(const string& s, int i) { return (s[i] >= 'a' && s[i] <= 'z'); }
    static shared_ptr<Variable> Create(const string& s, int& i);
    static string GetVar(const string& s, int& i);
    string Get() const { return var; }
protected:
    string var;
};