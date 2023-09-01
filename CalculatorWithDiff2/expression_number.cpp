#include "expression_number.hpp"

int Number::GetInt(const string& s, int& i)
{
    int n = 0;
    for (i; (s[i] >= '0' && s[i] <= '9') && (i < s.size()); i++)
        n = 10 * n + (s[i] - '0');
    return n;
}