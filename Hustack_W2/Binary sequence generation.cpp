/* Given an integer n, write a program that generates all the binary sequences of length n in a lexicographic order.
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
111 
*/

#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < (1 << n); i++) {
        int val = i;
        for (int j = n - 1; j >= 0; j--) {
            a[j] = val % 2;
            val /= 2;
        }
        for (int j = 0; j < n; j++) {
            cout << a[j];
        }
        cout << endl;
    }
    return 0;
}