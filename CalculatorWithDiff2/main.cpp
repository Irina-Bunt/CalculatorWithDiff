#include "expression.hpp"
#include "operation.hpp"
#include "expression_number.hpp"

#include "gtest/gtest.h"

#include <fstream>
#include <algorithm>

bool CheckContainsSubstr(const string& s, const string& substr, const int pos)
{
    if (s.size() < pos + substr.size())
        return false;
    for (int i = 0; i < substr.size(); i++) {
        if (s[pos + i] != substr[i])
            return false;
    }
    return true;
}

string GetSubstringAfterKey(const string& s, const string& key)
{
    if (CheckContainsSubstr(s, key, 0))
        return s.substr(key.size());
    return "";
}

string GetArgumentInBrackets(const string& s, const int pos)
{
    if (s[pos] != '(')
        return "";
    size_t n = s.find(')', pos + 1);
    if (n != string::npos)
        return s.substr(pos + 1, n - pos - 1);
    return "";
}

enum CommandStatus
{
    Ok = 0,
    Finish = 1,
    Failed = 2
};

class CommandRunnerInterface
{
public:
   virtual int ParseCommand(const string& s, const int pos) = 0;
   virtual shared_ptr<ExpressionInterface> RunCalculation(const ExpressionInterface&) = 0;
   virtual void PrintResult(ofstream& out, const string& s) const = 0;
   virtual string GetCommandName() const = 0;
   virtual CommandStatus GetStatus() = 0;
};

class CommandRunner : public CommandRunnerInterface
{
public:
    CommandRunner() {}
    virtual ~CommandRunner() {}
    int ParseCommand(const string& s, const int pos) override;
    shared_ptr<ExpressionInterface> RunCalculation(const ExpressionInterface&) override { return nullptr; }
    void PrintResult(ofstream& out, const string& s) const override;
    virtual string GetCommandName() const { return ""; }
    CommandStatus GetStatus() override { return state; }
protected:
    string arg;
    CommandStatus state;
};

int CommandRunner::ParseCommand(const string& s, const int pos)
{
    const string strName = GetCommandName();
    if (CheckContainsSubstr(s, strName, pos)) {
        arg = GetArgumentInBrackets(s, pos + 4);
        return strName.size() + 2;
    }
    return 0;
}

void CommandRunner::PrintResult(ofstream& out, const string& s) const
{
    // res_Simpl(): (20*2*x*xa-12*xa*xa)
    out << GetCommandName() << "(" << arg << "): " << s << std::endl;
}

class CommandRunnerDiff final : public CommandRunner
{
public:
    CommandRunnerDiff() {}
    shared_ptr<ExpressionInterface> RunCalculation(const ExpressionInterface& expr) override { state = Ok;  return expr.Diff(arg); }
    virtual string GetCommandName() const { return "Diff"; }
};

class CommandRunnerSimp final : public CommandRunner
{
public:
    CommandRunnerSimp() {}
    shared_ptr<ExpressionInterface> RunCalculation(const ExpressionInterface& expr) override { return expr.Simpl(); }
    virtual string GetCommandName() const { return "Simp"; }
};

class CommandRunnerCalc final : public CommandRunner
{
public:
    CommandRunnerCalc() {}
    shared_ptr<ExpressionInterface> RunCalculation(const ExpressionInterface& expr) override { return shared_ptr<Number>(new Number(expr.Calc(arg))); }
    virtual string GetCommandName() const { return "Calc"; }
};

class Calculator
{
public:
    Calculator(const string& strExpr, std::vector<CommandRunnerInterface*> commands, ofstream& out);
    ~Calculator();
    bool Calculate(const string& strOper);
private:
    string str;
    shared_ptr<ExpressionInterface> expr;
    std::vector<CommandRunnerInterface*> commands;
    ofstream& out;
};


Calculator::Calculator(const string& strExpr, std::vector<CommandRunnerInterface*> commands, ofstream& out)
: str(strExpr), commands(commands), out(out)
{
    expr = Expression::ConvertToExpressionsTree(strExpr);
}

Calculator::~Calculator()
{
    for (size_t i = 0; i < commands.size(); i++)
        delete commands[i];
}

bool Calculator::Calculate(const string& strOper)
{
    int pos = 0;
    while (pos < strOper.size()) {
        for (size_t i = 0; i < commands.size(); i++) {
            int charsParsed = commands[i]->ParseCommand(strOper, pos);
            if (charsParsed > 0) {
                expr = commands[i]->RunCalculation(*expr);
                if (expr == nullptr)
                    return false;
                commands[i]->PrintResult(out, expr->ToString());
                pos += charsParsed - 1;
                if (commands[i]->GetStatus() == Finish)
                    return true;
                break;
            }
        }
        pos += 1;
    }
    return true;
}

int main(int argc, char** argv)
{
    ofstream out("output.txt");
    ifstream in("input.txt");
    string s;
    while (getline(in, s))
    {
        string strExpr = GetSubstringAfterKey(s, "Expression: ");
        if (strExpr.empty()) {
            out << "INCORRECT" << endl;
            break;
        }
        getline(in, s);
        string strOper = GetSubstringAfterKey(s, "Operations: ");
        if (!strOper.empty()) {
            out << "Expression: " << strExpr << endl;
            Calculator calc(strExpr, { new CommandRunnerDiff, new CommandRunnerSimp, new CommandRunnerCalc }, out);
            calc.Calculate(strOper);
        }
        else
            out << "INCORRECT" << endl;
    }
    in.close();
    out.close();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}