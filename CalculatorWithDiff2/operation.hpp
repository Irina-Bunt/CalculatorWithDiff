#pragma once

#include "expression.hpp"

class Operation : public Expression
{
public:
    Operation(shared_ptr<ExpressionInterface> e0, shared_ptr<ExpressionInterface> e1) : e0(e0), e1(e1) {};
    shared_ptr<ExpressionInterface> Diff(const string& v) const override { return nullptr; };
    static int GetPriority(char ch);
public:
    shared_ptr<ExpressionInterface> e0;
    shared_ptr<ExpressionInterface> e1;
};


