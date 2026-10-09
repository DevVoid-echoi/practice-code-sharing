/* Given a positive integer N, generate all the ways to represent N as the sum of positive integers.
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

#include <bits/stdc++.h>
using namespace std;

void generatePartitions(int n, int minPart, vector<int>& current, vector<vector<int>>& result) {
    if (n == 0) {
        result.push_back(current);
        return;
    }

    for (int i = minPart; i <= n; ++i) {
        current.push_back(i);
        generatePartitions(n - i, i, current, result);
        current.pop_back();
    }
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> result;
    vector<int> current;

    generatePartitions(N, 1, current, result);

    for (const auto& partition : result) {
        for (size_t i = 0; i < partition.size(); ++i) {
            cout << partition[i];
            if (i < partition.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}