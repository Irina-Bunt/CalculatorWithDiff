#include "operation_add.hpp"
#include "operation_mul.hpp"
#include "expression_number.hpp"

shared_ptr<ExpressionInterface> OperationAdd::Simpl() const
{
    shared_ptr<ExpressionInterface> es0 = e0->Simpl();
    shared_ptr<ExpressionInterface> es1 = e1->Simpl();
    Number* n0 = dynamic_cast<Number*>(es0.get());
    Number* n1 = dynamic_cast<Number*>(es1.get());
    if (n0 && n1) {
        int n = n0->Get() + n1->Get();
        return shared_ptr<Number>(new Number(n));
    }
    if (es0->ToString() == es1->ToString()) {
        //delete es1;
        return shared_ptr<OperationMul>(new OperationMul(shared_ptr<Number>(new Number(2)), es0));
    }
    if (n0 && (n0->Get() == 0)) {
        //delete es0;
        return es1;
    }
    if (n1 && (n1->Get() == 0)) {
        //delete es1;
        return es0;
    }
    return shared_ptr<OperationAdd>(new OperationAdd(es0, es1));
};