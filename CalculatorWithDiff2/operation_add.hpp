#pragma once
#include "operation.hpp"

class OperationAdd final : public Operation
{
public:
    OperationAdd(shared_ptr<ExpressionInterface> ie0, shared_ptr<ExpressionInterface> ie1) : Operation(ie0, ie1) {}
    shared_ptr<ExpressionInterface> Clone() const override { return shared_ptr<OperationAdd>(new OperationAdd(e0->Clone(), e1->Clone())); }
    int Calc(const string& v) const override { return e0->Calc(v) + e1->Calc(v); }
    shared_ptr<ExpressionInterface> Diff(const string& v) const override { return shared_ptr<OperationAdd>(new OperationAdd(e0->Diff(v), e1->Diff(v))); }
    shared_ptr<ExpressionInterface> Simpl() const override;
    static bool Check(const string& s, int i) { return s[i] == '+'; }
    string ToString() const override { return "(" + e0->ToString() + "+" + e1->ToString() + ")"; }
};