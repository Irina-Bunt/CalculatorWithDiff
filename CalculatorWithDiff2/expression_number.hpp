#pragma once
#include "expression.hpp"

using namespace std;

class Number final : public Expression
{
public:
    Number(int inum) : num(inum) { };
    shared_ptr<ExpressionInterface> Clone() const override { return shared_ptr<Number>(new Number(num)); }
    string ToString() const override { return to_string(num); }
    int Calc(const string& v) const override { return num; }
    shared_ptr<ExpressionInterface> Diff(const string& v) const override { return shared_ptr<Number>(new Number(0)); }
    shared_ptr<ExpressionInterface> Simpl() const override { return shared_ptr<Number>(new Number(num)); }
    static bool Check(const string& s, int i) { return (s[i] >= '0' && s[i] <= '9'); }
    static shared_ptr<Number> Create(const string& s, int& i) { return shared_ptr<Number>(new Number(GetInt(s, i))); }
    static int GetInt(const string& s, int& i);
    int Get() const { return num; }

protected:
    int num;
};