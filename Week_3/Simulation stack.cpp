/*
Perform a sequence of operations over a stack, each element is an integer:
PUSH v: push a value v into the stack
POP: remove an element out of the stack and print this element to stdout (print NULL if the stack is empty)
Input
Each line contains a command (operration) of type 
PUSH  v
POP
Output
Write the results of POP operations (each result is written in a line)
Example
Input
PUSH 1
PUSH 2
PUSH 3
POP
POP
PUSH 4
PUSH 5
POP
#
Output
3
2
5
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    stack<long long> q;
    string cmd;
    while (cin >> cmd && cmd != "#") {
        if (cmd == "PUSH") {
            long long v;
            cin >> v;
            q.push(v);
        } else if (cmd == "POP") {
            if (q.empty()) {
                cout << "NULL\n";
            } else {
                cout << q.top() << '\n';
                q.pop();
            }
        }
    }

    return 0;
}
