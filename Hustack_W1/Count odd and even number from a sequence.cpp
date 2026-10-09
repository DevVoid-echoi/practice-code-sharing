#include <stdio.h>

using namespace std;

int main() {
    int n, odd = 0, even = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    printf("%d %d", odd, even);
    return 0;
}