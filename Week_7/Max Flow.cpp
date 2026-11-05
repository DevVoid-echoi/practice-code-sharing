/*
Given a network G = (V, E) which is a directed weighted graph. Node s is the source and node t is the target. c(u,v) is the capacity of the arc (u,v). Find the maximum flow on G.
Input
•Line 1: two positive integers N and M (1 <= N <= 10
4
, 1 <= M <= 10
6
)
•Line 2: contains 2 positive integers s and t
•Line i+2 (I = 1,. . ., M): contains two positive integers u and v which are endpoints of i
th
 arc
Output
  Write the value of the max-flow found
Example
Input
7 12
6 7
1 7 7
2 3 6
2 5 6
3 1 6
3 7 11
4 1 7
4 2 4
4 5 5
5 1 4
5 3 4
6 2 8
6 4 10
Output
17
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long cap;
};

int n;
vector<Edge> edges;
vector<vector<int>> g;
vector<int> level, it;

void addEdge(int u, int v, long long c) {
    g[u].push_back(edges.size());
    edges.push_back({v, c});
    g[v].push_back(edges.size());
    edges.push_back({u, 0});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e : g[u]) {
            if (edges[e].cap > 0 && level[edges[e].to] < 0) {
                level[edges[e].to] = level[u] + 1;
                q.push(edges[e].to);
            }
        }
    }
    return level[t] >= 0;
}

long long dfs(int u, int t, long long f) {
    if (u == t) return f;
    for (int &i = it[u]; i < (int)g[u].size(); i++) {
        int e = g[u][i];
        int v = edges[e].to;
        if (edges[e].cap > 0 && level[v] == level[u] + 1) {
            long long d = dfs(v, t, min(f, edges[e].cap));
            if (d > 0) {
                edges[e].cap -= d;
                edges[e ^ 1].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, s, t;
    cin >> n >> m >> s >> t;
    g.assign(n + 1, {});
    edges.reserve(2 * m);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    level.assign(n + 1, -1);
    it.assign(n + 1, 0);
    long long flow = 0;
    if (s != t) {
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            long long f;
            while ((f = dfs(s, t, 4e18)) > 0) flow += f;
        }
    }
    cout << flow << '\n';

    return 0;
}
