/*Given two positive integers k and n. Compute C(k,n) which is the number of ways to select k objects from a given set of n objects.
Input
Line 1: two positive integers k and n (1 <= k,n <= 999)
Output
Write te value C(k,n) modulo 10
9
+7.
Example
Input
3  5
Output
10*/

#include <iostream>

using namespace std;

const int MOD = 1000000007;
int C[1001][1001];

int main () {
    int k, n;
    cin >> k >> n;

    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    if (k > n) cout << 0;
    else cout << C[n][k];

    return 0;
}
