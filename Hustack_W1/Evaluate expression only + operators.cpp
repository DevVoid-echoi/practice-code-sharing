/* Given a string representing a math expression including operator +  and operands (positive integers). Compute the value Q of this expression.
Input
Line 1: contains the string representing the expression (number of operators is upto 10000)
Output
Write the value Q modulo 109+7 if the expression is mathematically correct in term of the syntax, and write NOT_CORRECT, otherwise
Example
Input
2+1+7+4
Output
14
Input
2+1+7+4 +
Output
NOT_CORRECT */

#include <iostream>
#include <string>

using namespace std;

int main () {
    string expression;
    getline(cin, expression);

    long long result = 0;
    long long current_number = 0;
    bool last_was_operator = true; // To check if the last character was an operator

    for (char c : expression) {
        if (isdigit(c)) {
            current_number = current_number * 10 + (c - '0');
            last_was_operator = false;
        } else if (c == '+') {
            if (last_was_operator) {
                cout << "NOT_CORRECT" << endl;
                return 0;
            }
            result = (result + current_number) % 1000000007;
            current_number = 0;
            last_was_operator = true;
        } else {
            cout << "NOT_CORRECT" << endl;
            return 0;
        }
    }

    if (last_was_operator) {
        cout << "NOT_CORRECT" << endl;
        return 0;
    }

    result = (result + current_number) % 1000000007;

    cout << result << endl;

    return 0;
}