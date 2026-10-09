/* here are two jugs, a-litres jug and b-litres jug (a, b are positive integers). There is a pump with unlimited water. Given a positive integer c, how to get exactly c litres.
Input
   Line 1: contains positive integers a,   b,  c  (1 <= a, b, c <= 900)
Output
  write the number of steps or write -1 (if no solution found)
Example

Input
6  8  4
Output
4 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    if (c > max(a, b) || c < 0) {
        cout << -1 << '\n';
        return 0;
    }

    int g = gcd(a, b);
    if (c % g != 0) {
        cout << -1 << '\n';
        return 0;
    }

    queue<pair<int, int>> q;
    unordered_map<int, int> dist;
    auto encode = [&](int x, int y) {
        return (x << 16) ^ y;
    };

    q.push({0, 0});
    dist[encode(0, 0)] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == c || y == c) {
            cout << dist[encode(x, y)] << '\n';
            return 0;
        }

        auto pushState = [&](int nx, int ny) {
            int key = encode(nx, ny);
            if (!dist.count(key)) {
                dist[key] = dist[encode(x, y)] + 1;
                q.push({nx, ny});
            }
        };

        // Fill jug A
        pushState(a, y);
        // Fill jug B
        pushState(x, b);
        // Empty jug A
        pushState(0, y);
        // Empty jug B
        pushState(x, 0);

        // Pour A -> B
        if (x > 0) {
            int transfer = min(x, b - y);
            pushState(x - transfer, y + transfer);
        }

        // Pour B -> A
        if (y > 0) {
            int transfer = min(y, a - x);
            pushState(x + transfer, y - transfer);
        }
    }

    cout << -1 << '\n';
    return 0;
}

