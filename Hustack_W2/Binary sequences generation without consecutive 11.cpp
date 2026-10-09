/* Given an integer n, write a program that generates all binary sequences without consecutive 11 in a lexicographic order.
Input
Line 1: contains an integer n (1 <= n <= 20)
Output
Write binary sequences in a lexicographic order, each sequence in a line
Example
Input
3
Output
000
001
010
100
101 */

#include <bits/stdc++.h>
using namespace std;

vector<string> sequences;

void generateSequences(int n, string current) {
    if (current.length() == n) {
        sequences.push_back(current);
        return;
    }

    generateSequences(n, current + "0");

    if (current.empty() || current.back() != '1') {
        generateSequences(n, current + "1");
    }
}

int main() {
    int n;
    cin >> n;

    generateSequences(n, "");

    for (const string& seq : sequences) {
        cout << seq << '\n';
    }

    return 0;
}
