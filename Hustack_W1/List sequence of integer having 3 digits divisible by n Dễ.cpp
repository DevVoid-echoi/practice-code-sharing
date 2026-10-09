#include <iostream>
#include <math.h>

using namespace std;

int main () {
    int n;
    cin >> n;

    for (int i = 100; i <= 999; i++) {
        if (i % n == 0) {
            cout << i << " ";
        }
    }
    return 0;
}