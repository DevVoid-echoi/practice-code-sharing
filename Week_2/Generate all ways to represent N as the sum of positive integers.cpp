/*Given a positive integer N, generate all the ways to represent N as the sum of positive integers.
         N = x[1] + x[2] + . . . + x[k]  with 1 <= x[1] <= x[2] <= . . . <= x[k]

Input
Line 1: contains a positive integer N (1 <= N <= 20)

Output
Each line contains a sequence of positive integers sorted in non-decreasing order such that the sum is equal to N
(solutions are displayed in a lexicographic order)

Example
Input
4

Output 
1 1 1 1
1 1 2
1 3
2 2
4
*/

#include <iostream>

using namespace std;

int n;
int x[25];

void Try(int k, int rem) {
    if (rem == 0) {
        for (int i = 0; i < k; i++) {
            if (i > 0) cout << ' ';
            cout << x[i];
        }
        cout << '\n';
        return;
    }
    int start = (k == 0 ? 1 : x[k - 1]);
    for (int v = start; v <= rem; v++) {
        x[k] = v;
        Try(k + 1, rem - v);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    Try(0, n);

    return 0;
}
