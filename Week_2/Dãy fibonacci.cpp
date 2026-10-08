/*Given a fibonacci sequence a[0], a[1], a[2], ... in which:  a[0] = 0, a[1] = 1, a[n] = a[n-1] + a[n-2], for all n >= 2
Given  positive integer n, compute a[n-1].
Input
Line 1: contains a positive integer n (2 <= n <= 21)
Output
Write a[n-1]
Example
Input
9
Output
21*/

#include <iostream>

using namespace std;

int main () {
    int n;
    cin >> n;

    long long a = 0, b = 1;
    for (int i = 0; i < n - 1; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    cout << a;

    return 0;
}
