/*Given an integer n, write a program that generates all the binary sequences of length n in a lexicographic order.
Input
Line 1: contains an integer n (1 <= n <= 20)
Output
Write binary sequences in a lexicographic ordder, eac sequence in a line

Example
Input
3
Output
000
001
010
011
100
101
110
111*/

#include <iostream>

using namespace std;

int n;
char x[25];

void Try(int k) {
    if (k == n) {
        cout << x << '\n';
        return;
    }
    for (char v = '0'; v <= '1'; v++) {
        x[k] = v;
        Try(k + 1);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    x[n] = '\0';
    Try(0);

    return 0;
}
