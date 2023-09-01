#include "operation.hpp"

int Operation::GetPriority(char ch) {
    switch (ch) {
    case '+': return 0;
    case '-': return 1;
    case '*': return 2;
    case '/': return 3;
    }
    return 0; // Error
}

