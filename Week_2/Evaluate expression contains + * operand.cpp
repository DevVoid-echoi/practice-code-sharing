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
NOT_CORRECT*/

#include <iostream>
#include <string>

using namespace std;

const long long MOD = 1000000007;

int main () {
    string s;
    getline(cin, s);

    long long sum = 0, term = 1, num = 0;
    bool expectNumber = true, inNumber = false, correct = true;

    for (size_t i = 0; i <= s.size() && correct; i++) {
        char ch = (i < s.size() ? s[i] : '\0');

        if (ch >= '0' && ch <= '9') {
            if (!inNumber && !expectNumber) correct = false;
            inNumber = true;
            expectNumber = false;
            num = (num * 10 + (ch - '0')) % MOD;
            continue;
        }

        if (inNumber) {
            term = term * num % MOD;
            num = 0;
            inNumber = false;
        }

        if (ch == ' ' || ch == '\t' || ch == '\r') continue;

        if (ch == '+' || ch == '*' || ch == '\0') {
            if (expectNumber) {
                correct = false;
                break;
            }
            if (ch == '+' || ch == '\0') {
                sum = (sum + term) % MOD;
                term = 1;
            }
            expectNumber = true;
        } else {
            correct = false;
        }
    }

    if (correct) cout << sum;
    else cout << "NOT_CORRECT";

    return 0;
}
