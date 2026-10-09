/*Given a sequence of integers a1, a2, ..., an. Perform a sequence of queries over this sequence including:
find-max: return the maximum element of the given sequence
find-min: return the minimum element of the given sequence 
sum: return the sum of the elements of the given sequence 
find-max-segment i j: return the maximum element of the subsequence from index i to index j (i <= j)

Input
The first block contains the information about the given sequence with the following format:
Line 1: contains a positive integer n (1 <= n <= 10000)
Line 2: contains n integers a1, a2, ..., an (-1000 <= ai <= 1000)
The first block is terminated by a character *
The second block contains a sequence of queries defined above, each query is in a line. The second block is terminated a 3 characters ***

Output
Write the result of each query in a corresponding line*/
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main () {
    int n;
    cin >> n;
    int arr [n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    string query;
    cin >> query;

    while (cin >> query && query != "***") {
        if (query == "find-max") {
            int max_val = *max_element(arr, arr + n);
            cout << max_val << endl;
        } else if (query == "find-min") {
            int min_val = *min_element(arr, arr + n);
            cout << min_val << endl;
        } else if (query == "sum") {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += arr[i];
            }
            cout << sum << endl;
        } else if (query == "find-max-segment") {
            int i, j;
            cin >> i >> j;
            int max_segment = INT_MIN;
            for (int k = i - 1; k < j; k++) {
                max_segment = max(max_segment, arr[k]);
            }
            cout << max_segment << endl;
        }
    }
    
    return 0;
}

