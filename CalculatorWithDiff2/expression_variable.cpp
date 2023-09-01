#include "expression_variable.hpp"

// "x,30;y,1;ab,5"
int Variable::Calc(const string& s) const
{
    string v = s + ";";
    string varRepl;
    int numRepl = 0;
    int i = 0;
    while (i < v.length()) {
        if ((v[i] == ';') && (var == varRepl))
            return numRepl;
        else if (Number::Check(v, i))
            numRepl = Number::GetInt(v, i);
        else if (Variable::Check(v, i))
            varRepl = Variable::GetVar(v, i);
        else
            i++;
    }
    return 0;
    //cout << "Variable for replacement not found :(";
    //exit(0);
}

shared_ptr<Variable> Variable::Create(const string& s, int& i)
{
    string str;
    for (i; (s[i] >= 'a' && s[i] <= 'z') && (i < s.size()); i++)
        str += s[i];
    return shared_ptr<Variable>(new Variable(str));
};

string Variable::GetVar(const string& s, int& i)
{
    string str;
    for (; (s[i] >= 'a' && s[i] <= 'z') && (i < s.size()); i++)
        str += s[i];
    return str;
}
