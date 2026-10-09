/* Given a fibonacci sequence a[0], a[1], a[2], ... in which:  a[0] = 0, a[1] = 1, a[n] = a[n-1] + a[n-2], for all n >= 2
Given  positive integer n, compute a[n-1].
Input
Line 1: contains a positive integer n (2 <= n <= 21)
Output
Write a[n-1] */

#include <iostream>
using namespace std;

int main () {
    int n; 
    cin >> n;
    int a[n];
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i < n; i++) {
        a[i] = a[i-1] + a[i-2];
    }
    cout << a[n-1];
    return 0;
}