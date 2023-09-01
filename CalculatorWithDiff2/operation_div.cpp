#include "operation_div.hpp"
#include "expression_number.hpp"

shared_ptr<ExpressionInterface> OperationDiv::Diff(const string& v) const
{
    return shared_ptr<OperationDiv>(new OperationDiv(
        shared_ptr<OperationSub>(new OperationSub(shared_ptr<OperationMul>(new OperationMul(e0->Diff(v), e1->Clone())), shared_ptr<OperationMul>(new OperationMul(e0->Clone(), e1->Diff(v))))),
        shared_ptr<OperationMul>(new OperationMul(e1->Clone(), e1->Clone()))));
}

shared_ptr<ExpressionInterface> OperationDiv::Simpl() const
{
    shared_ptr<ExpressionInterface> es0 = e0->Simpl();
    shared_ptr<ExpressionInterface> es1 = e1->Simpl();
    Number* n0 = dynamic_cast<Number*>(es0.get());
    Number* n1 = dynamic_cast<Number*>(es1.get());
    if (n0 && n1 && (n1->Get() != 0)) {
        int n = n0->Get() / n1->Get();
        if ((double)n == (double)n0->Get() / (double)n1->Get()) {
            //delete es0;
            //delete es1;
            return shared_ptr<Number>(new Number(n));
        }
    }
    return shared_ptr<OperationDiv>(new OperationDiv(es0, es1));
};