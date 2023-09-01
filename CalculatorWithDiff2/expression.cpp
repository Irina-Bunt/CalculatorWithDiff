#include "expression_number.hpp"
#include "expression_variable.hpp"
#include "operation_add.hpp"
#include "operation_sub.hpp"
#include "operation_mul.hpp"
#include "operation_div.hpp"

#include <iostream>
#include <string>
#include <stack>

using namespace std;


bool Expression::CheckOperation(const char ch)
{
    string s;
    s += ch;
    return OperationAdd::Check(s, 0) || OperationSub::Check(s, 0) || OperationMul::Check(s, 0) || OperationDiv::Check(s, 0);
}

shared_ptr<Expression> Expression::ConvertToExpressionsTree(const string& s)
{
    string polNotation = ToPolNotation(s);
    shared_ptr<Expression> exprTree = PolNotationToExprTree(polNotation);
    return exprTree;
}

string Expression::ToPolNotation(const string& s)
{
    stack<char> st;
    string res;
    int i = 0;
    while (i < s.length()) {
        if (s[i] == '(') {
            i++;
            st.push('(');
        }
        else if (s[i] == ')') {
            i++;
            while (st.top() != '(') {
                res += string(1, st.top()) + " ";
                st.pop();
            }
            st.pop();
        }
        else if (Number::Check(s, i)) {
            int i0 = i;
            Number::GetInt(s, i);
            res += s.substr(i0, i - i0) + " ";
        }
        else if (Variable::Check(s, i)) {
            int i0 = i;
            Variable::GetVar(s, i);
            res += s.substr(i0, i - i0) + " ";
        }
        else if (CheckOperation(s[i])) {
            char ch = s[i++];
            while (!st.empty() && CheckOperation(st.top()) && (Operation::GetPriority(st.top()) > Operation::GetPriority(ch))) {
                res += string(1, st.top()) + " ";
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        res += string(1, st.top()) + " ";
        st.pop();
    }
    return res;
}

shared_ptr<Expression> Expression::PolNotationToExprTree(const string& s)
{
    stack<shared_ptr<Expression>> st;
    int i = 0;
    while (i < s.length()) {
        if (Number::Check(s, i)) {
            st.push(Number::Create(s, i));
            i++;
        }
        else if (Variable::Check(s, i)) {
            st.push(Variable::Create(s, i));
            i++;
        }
        else if (CheckOperation(s[i])) {
            char ch = s[i];
            shared_ptr<ExpressionInterface> ex1 = st.top();
            st.pop();
            shared_ptr<ExpressionInterface> ex0 = st.top();
            st.pop();
            if (OperationAdd::Check(s, i))
                st.push(shared_ptr<OperationAdd>(new OperationAdd(ex0, ex1)));
            else if (OperationSub::Check(s, i))
                st.push(shared_ptr<OperationSub>(new OperationSub(ex0, ex1)));
            else if (OperationMul::Check(s, i))
                st.push(shared_ptr<OperationMul>(new OperationMul(ex0, ex1)));
            else if (OperationDiv::Check(s, i))
                st.push(shared_ptr<OperationDiv>(new OperationDiv(ex0, ex1)));
            i += 2;
        }
    }
    return st.top();
}
