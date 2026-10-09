/* Given two positive integers k and n. Compute C(k,n) which is the number of ways to select k objects from a given set of n objects.
Input
Line 1: two positive integers k and n (1 <= k,n <= 999)
Output
Write te value C(k,n) modulo 10e9+7.
Example
Input
3  5
Output
10
*/

#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007LL;

long long C(int k, int n) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }

    long long dp[1000 + 1] = {0};
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = min(i, k); j >= 1; --j) {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }

    return dp[k];
}

int main() {
    int k, n;
    cin >> k >> n;
    cout << C(k, n) << endl;
    return 0;
}
