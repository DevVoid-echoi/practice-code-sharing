/*
Cho dãy a1, a2, ..., an trong đó các phần tử đôi một khác nhau và 1 giá trị nguyên dương M. Hãy đếm số Q các cặp (i,j) sao cho 1 <= i < j <= n và ai + aj = M.

Dữ liệu
Dòng 1: ghi n và M (1 <= n, M <= 1000000)
Dòng 2: ghi a1, a2, ..., an
Kết quả
Ghi ra giá trị Q
Ví dụ
Dữ liệu
5 6
5 2 1 4 3
Kết quả
2
*/
#include <iostream>
#include <vector>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<char> seen(m + 1, 0);
    long long q = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x < m && seen[m - x]) q++;
        if (x <= m) seen[x] = 1;
    }
    cout << q << '\n';

    return 0;
}
