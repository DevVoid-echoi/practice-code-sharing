/*
Given a string containing only characters (, ), [, ] {, }. Write a program that checks whether the string is correct in expression.
Example
 ([]{()}()[]): correct
 ([]{()]()[]): incorrect
Input
One line contains the string (the length of the string is less than or equal to $10^6$)One line contains the string (the length of the string is less than or equal to 10
6
)
Output
Write 1 if the sequence is correct, and write 0, otherwise
Example
Input
(()[][]{}){}{}[][]({[]()})
Output
1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<char> st;
    st.reserve(s.size());
    bool ok = true;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push_back(c);
        } else {
            if (st.empty()) { ok = false; break; }
            char t = st.back();
            st.pop_back();
            if ((c == ')' && t != '(') || (c == ']' && t != '[') || (c == '}' && t != '{')) {
                ok = false;
                break;
            }
        }
    }
    if (!st.empty()) ok = false;
    cout << (ok ? 1 : 0) << '\n';

    return 0;
}
