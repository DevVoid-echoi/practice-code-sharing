#include <iostream>

using namespace std;

int main () {
    int n, k;
    cin >> n >> k;
    int count = 0;
    int x[n];
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    for (int i = 0; i < n-k+1; i++) {
        int sum = 0;
        for (int j = i; j < i+k; j++) {
            sum += x[j];
        }
        if (sum % 2 == 0) {
            count++;
        }
    }
    cout << count;

    return 0;
}