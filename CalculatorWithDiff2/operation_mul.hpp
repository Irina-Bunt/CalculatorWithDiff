#pragma once
#include "operation_add.hpp"

class OperationMul final : public Operation
{
public:
    OperationMul(shared_ptr<ExpressionInterface> e0, shared_ptr<ExpressionInterface> e1) : Operation(e0, e1) {};
    shared_ptr<ExpressionInterface> Clone() const override { return shared_ptr<OperationMul>(new OperationMul(e0->Clone(), e1->Clone())); }
    string ToString() const override { return e0->ToString() + "*" + e1->ToString(); }
    int Calc(const string& v) const override { return e0->Calc(v) * e1->Calc(v); }
    shared_ptr<ExpressionInterface> Diff(const string& v) const override;
    shared_ptr<ExpressionInterface> Simpl() const override;
    static bool Check(const string& s, int i) { return s[i] == '*'; }
};