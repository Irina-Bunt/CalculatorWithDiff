#pragma once

#include <string>
#include <memory>

using namespace std;

class ExpressionInterface
{
public:
    virtual ~ExpressionInterface() {}
    virtual shared_ptr<ExpressionInterface> Clone() const = 0;
    virtual string ToString() const = 0;
    virtual shared_ptr<ExpressionInterface> Diff(const string& v) const = 0;
    virtual int Calc(const string& v) const = 0;
    virtual shared_ptr<ExpressionInterface> Simpl() const = 0;
};

class Expression : public ExpressionInterface
{
public:
    Expression() {};
    shared_ptr<ExpressionInterface> Clone() const override { return nullptr; };
    string ToString() const override { return ""; };
    shared_ptr<ExpressionInterface> Diff(const string& v) const override { return nullptr; };
    int Calc(const string& v) const override { return 0; }
    shared_ptr<ExpressionInterface> Simpl() const override { return nullptr; };
    static bool CheckOperation(const char ch);
    static shared_ptr<Expression> ConvertToExpressionsTree(const string& s);
    static string ToPolNotation(const string& s);
    static shared_ptr<Expression> PolNotationToExprTree(const string& s);
};

