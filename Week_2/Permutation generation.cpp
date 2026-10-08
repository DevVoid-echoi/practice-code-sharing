/*Given an integer n, write a program to generate all permutations of 1, 2, ..., n in a lexicalgraphic order (elements of a permutation are separated by a SPACE character).
Example
Input 
3
Output
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 */

#include <iostream>

using namespace std;

int n;
int x[25];
bool used[25];

void Try(int k) {
    if (k == n) {
        for (int i = 0; i < n; i++) cout << x[i] << ' ';
        cout << '\n';
        return;
    }
    for (int v = 1; v <= n; v++) {
        if (used[v]) continue;
        used[v] = true;
        x[k] = v;
        Try(k + 1);
        used[v] = false;
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    Try(0);

    return 0;
}
