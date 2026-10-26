/*
Given a string T and a pattern P which is also a string. Find the number of occurrences of P in T.
Input
Line 1: contains string P (length is less than or equals to 10
5
)
Line 2: contains the string T (length is less than or equals to 10
6
)
Output
Write the number of occurrences of P in T
Exmple
Input
computer
There are so many kinds of computers today including high performance computers, laptop computers. Mobile phones are also computers
Output
4
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string p, t;
    getline(cin, p);
    getline(cin, t);
    if (!p.empty() && p.back() == '\r') p.pop_back();
    if (!t.empty() && t.back() == '\r') t.pop_back();

    int n = p.size();
    if (n == 0 || n > (int)t.size()) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> pi(n, 0);
    for (int i = 1, k = 0; i < n; i++) {
        while (k > 0 && p[i] != p[k]) k = pi[k - 1];
        if (p[i] == p[k]) k++;
        pi[i] = k;
    }

    long long cnt = 0;
    for (int i = 0, k = 0; i < (int)t.size(); i++) {
        while (k > 0 && t[i] != p[k]) k = pi[k - 1];
        if (t[i] == p[k]) k++;
        if (k == n) {
            cnt++;
            k = pi[k - 1];
        }
    }
    cout << cnt << '\n';

    return 0;
}
