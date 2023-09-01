#include "operation_mul.hpp"
#include "expression_number.hpp"

shared_ptr<ExpressionInterface> OperationMul::Diff(const string& v) const
{
    return shared_ptr<OperationAdd>(new OperationAdd(shared_ptr<OperationMul>(new OperationMul(e0->Diff(v), e1->Clone())),
                                                     shared_ptr<OperationMul>(new OperationMul(e0->Clone(), e1->Diff(v)))));
}

shared_ptr<ExpressionInterface> OperationMul::Simpl() const
{
    shared_ptr<ExpressionInterface> es0 = e0->Simpl();
    shared_ptr<ExpressionInterface> es1 = e1->Simpl();
    Number* n0 = dynamic_cast<Number*>(es0.get());
    Number* n1 = dynamic_cast<Number*>(es1.get());
    if (n0 && n1) {
        int n = n0->Get() * n1->Get();
        return shared_ptr<Number>(new Number(n));
    }
    if (n0 && (n0->Get() == 0) || n1 && (n1->Get() == 0)) {
        return shared_ptr<Number>(new Number(0));
    }
    if (n0 && (n0->Get() == 1)) {
        return es1;
    }
    if (n1 && (n1->Get() == 1)) {
        return es0;
    }
    return shared_ptr<OperationMul>(new OperationMul(es0, es1));
};