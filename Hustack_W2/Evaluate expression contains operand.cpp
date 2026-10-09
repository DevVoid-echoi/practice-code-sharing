/*Given a string representing a math expression including operator + and * and operands which are positive integers. Compute the value Q of this expression.
Input
Line 1: contains the string representing the expression (number of operators is upto 10000)
Output
Write the value Q modulo 10
9
+7 if the expression is mathematically correct in term of the syntax, and write NOT_CORRECT, otherwise
Example
Input
5+7*3*10*10
Output
2105
Input
5*+ 7*3*10*10
Output
NOT_CORRECT */

#include <bits/stdc++.h>
using namespace std;

bool isValidExpression(const string& expr) {
    int n = expr.size();
    if (n == 0) return false;

    // Check for invalid characters
    for (char c : expr) {
        if (!isdigit(c) && c != '+' && c != '*') {
            return false;
        }
    }

    // Check for consecutive operators or operators at the start/end
    if (expr[0] == '+' || expr[0] == '*' || expr[n - 1] == '+' || expr[n - 1] == '*') {
        return false;
    }

    for (int i = 1; i < n; ++i) {
        if ((expr[i] == '+' || expr[i] == '*') && (expr[i - 1] == '+' || expr[i - 1] == '*')) {
            return false;
        }
    }

    return true;
}

int evaluateExpression(const string& expr) {
    long long result = 0;
    long long currentProduct = 1;
    long long currentNumber = 0;
    bool hasNumber = false;

    for (char c : expr) {
        if (isdigit(c)) {
            currentNumber = currentNumber * 10 + (c - '0');
            hasNumber = true;
        } else if (c == '*') {
            if (!hasNumber) return -1; // Invalid syntax
            currentProduct *= currentNumber;
            currentNumber = 0;
            hasNumber = false;
        } else if (c == '+') {
            if (!hasNumber) return -1; // Invalid syntax
            currentProduct *= currentNumber;
            result += currentProduct;
            result %= 1000000007; // Modulo operation
            currentProduct = 1;
            currentNumber = 0;
            hasNumber = false;
        }
    }

    if (hasNumber) {
        currentProduct *= currentNumber;
        result += currentProduct;
        result %= 1000000007; // Modulo operation
    }

    return result;
}

int main() {
    string expression;
    cin >> expression;

    if (!isValidExpression(expression)) {
        cout << "NOT_CORRECT" << endl;
        return 0;
    }

    int result = evaluateExpression(expression);
    if (result == -1) {
        cout << "NOT_CORRECT" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
