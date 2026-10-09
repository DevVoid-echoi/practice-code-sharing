/* Given an integer n, write a program to generate all permutations of 1, 2, ..., n in a lexicalgraphic order (elements of a permutation are separated by a SPACE character).
Example
Input 
3
Output
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 
*/

#include <iostream>
using namespace std;

int n;
int used[100];
int a[100];

void generate(int k) {
    if (k == n) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << (i == n - 1 ? '\n' : ' ');
        }
        return;
    }

    for (int value = 1; value <= n; value++) {
        if (!used[value]) {
            used[value] = 1;
            a[k] = value;
            generate(k + 1);
            used[value] = 0;
        }
    }
}

int main() {
    cin >> n;
    generate(0);
    return 0;
}