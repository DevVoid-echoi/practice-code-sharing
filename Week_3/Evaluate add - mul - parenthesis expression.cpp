/*
Given a string representing a math expression including operator + and * and operands which are positive integer and parentheses. Compute the value Q of this expression.
Input
Line 1: contains the string representing the expression (number of operators is upto 10000)
Output
Write the value Q modulo 10
9
+7 if the expression is mathematically correct in term of the syntax, and write NOT_CORRECT, otherwise
Example
Input
(2+4*10)*(5) + 7
Output
217

Input
((2+4*10)*(5) + 7
Output
NOT_CORRECT
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 1000000007LL;

vector<long long> vals;
vector<char> ops;

void applyOp() {
    long long b = vals.back(); vals.pop_back();
    long long a = vals.back(); vals.pop_back();
    char op = ops.back(); ops.pop_back();
    if (op == '+') vals.push_back((a + b) % MOD);
    else vals.push_back(a * b % MOD);
}

int prec(char op) {
    return op == '*' ? 2 : (op == '+' ? 1 : 0);
}

int main () {
    string s, line;
    while (getline(cin, line)) s += line + ' ';

    bool expectOperand = true;
    int depth = 0;
    bool ok = true;
    size_t n = s.size();
    for (size_t i = 0; i < n && ok; i++) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;
        if (isdigit((unsigned char)c)) {
            if (!expectOperand) { ok = false; break; }
            long long v = 0;
            while (i < n && isdigit((unsigned char)s[i])) {
                v = (v * 10 + (s[i] - '0')) % MOD;
                i++;
            }
            i--;
            vals.push_back(v);
            expectOperand = false;
        } else if (c == '(') {
            if (!expectOperand) { ok = false; break; }
            ops.push_back('(');
            depth++;
        } else if (c == ')') {
            if (expectOperand || depth == 0) { ok = false; break; }
            while (ops.back() != '(') applyOp();
            ops.pop_back();
            depth--;
        } else if (c == '+' || c == '*') {
            if (expectOperand) { ok = false; break; }
            while (!ops.empty() && prec(ops.back()) >= prec(c)) applyOp();
            ops.push_back(c);
            expectOperand = true;
        } else {
            ok = false;
        }
    }
    if (expectOperand || depth != 0) ok = false;

    if (!ok) {
        cout << "NOT_CORRECT\n";
        return 0;
    }
    while (!ops.empty()) applyOp();
    cout << vals.back() << '\n';

    return 0;
}
