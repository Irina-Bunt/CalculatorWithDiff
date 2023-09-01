#include "expression.hpp"
#include "operation.hpp"

#include <iostream>
#include "gtest/gtest.h"

TEST(Operations, OperationAdd_var) {
    const string s = "x+x";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    shared_ptr<ExpressionInterface> exprTest0 = exprTree->Simpl();
    ASSERT_TRUE(exprTest0->ToString() == "2*x");
}
TEST(Operations, OperationAdd) {
    const string s = "x+x+2+2";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    int exprTest1 = exprTree->Calc("x=2");
    ASSERT_TRUE(exprTest1 == 8);
}

TEST(Operations, OperationSub_var_null) {
    const string s = "x-x";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    shared_ptr<ExpressionInterface> exprTest0 = exprTree->Simpl();
    //cout << exprTest0->ToString() << endl;
    ASSERT_TRUE(exprTest0->ToString() == "0");
}
TEST(Operations, OperationSub) {
    const string s = "2*x-x";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    int exprTest1 = exprTree->Calc("x=2");
    ASSERT_TRUE(exprTest1 == 2);
}

TEST(Operations, Diff_1) {
    const string s = "2*x*x*x";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    shared_ptr<ExpressionInterface> exprDiff0 = exprTree->Diff("x");
    ASSERT_TRUE(exprDiff0->Simpl()->ToString() == "2*(x*x+x*2*x)");
}
TEST(Operations, Diff_2) {
    const string s = "2*x*x*x";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    shared_ptr<ExpressionInterface> exprDiff0 = exprTree->Diff("x");
    shared_ptr<ExpressionInterface> exprDiff1 = exprDiff0->Diff("x");
    ASSERT_TRUE(exprDiff1->Simpl()->ToString() == "2*(2*x+(2*x+x*2))");
}
TEST(Operations, Diff_x_Diff_y) {
    const string s = "2*x*y+x*x*y*y";
    shared_ptr<Expression> exprTree = Expression::ConvertToExpressionsTree(s);
    shared_ptr<ExpressionInterface> exprDiff0 = exprTree->Diff("x");
    shared_ptr<ExpressionInterface> exprDiff1 = exprDiff0->Diff("y");
    ASSERT_TRUE(exprDiff1->Simpl()->ToString() == "(2+2*x*2*y)");
}