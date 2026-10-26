/*
Given an undirected graph G = (V,E). Write a program to check if G is a Hamiltonian graph.
Input
Line 1: a positive integer T (number of graphs)
Subsequent lines are information about T graphs, each has the following format:
Line 1: n and m (number of nodes and edges)
Line i+1 (i = 1, 2, ..., m): u and v : two end points of the ith edge
Output
In the i
th
 line, write 1 if the corresponding is a Hamiltonian graph, and write 0, otherwise
Example
Input
2
5 5
1 2
1 3
2 4
2 5
3 5
7 13
1 3
1 5
1 7
2 4
2 5
2 6
3 4
3 5 
3 7
4 6
4 7
5 7
6 7

Output
0
1
*/
#include <iostream>
#include <vector>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> adj(n, 0);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u] |= 1 << v;
            adj[v] |= 1 << u;
        }

        int full = (1 << n) - 1;
        vector<int> dp(1 << n, 0);
        dp[1] = 1;
        for (int mask = 1; mask <= full; mask++) {
            if (!(mask & 1) || !dp[mask]) continue;
            for (int u = 0; u < n; u++) {
                if (!(dp[mask] >> u & 1)) continue;
                int nxt = adj[u] & ~mask;
                while (nxt) {
                    int v = __builtin_ctz(nxt);
                    nxt &= nxt - 1;
                    dp[mask | (1 << v)] |= 1 << v;
                }
            }
        }

        bool ok = false;
        for (int u = 0; u < n && !ok; u++)
            if ((dp[full] >> u & 1) && (adj[u] & 1)) ok = true;
        if (n == 1) ok = true;
        cout << (ok ? 1 : 0) << '\n';
    }

    return 0;
}
