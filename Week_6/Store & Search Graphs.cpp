/*
Two undirected graphs G1 = (V1, E1) and G2 = (V2,E2) have the same structure (G1 and G2 are isomorphic) if and only if there exists a bijective function f: V1 -> V2 such that (u,v) in E1 iff (f(v), f(v)) in E2.
Given a sequence of undirected graph G = g1, g2, . . ., gN. Perform K queries to check whether or not a given graph hk (k = 1, 2, . . ., K) is present in G (there exists a graph of G which has the same structure with hk).
Input
The input consists of 2 blocks:
	The first blocks are N graphs with the format:
	Line 1: contains a positive integer N (1 <= N <= 10000)
	Subsequent lines contain the information about n graphs g1, g2, . . ., gN with the format:
	Line 1: contains 2 integer n and m which are the number of nodes and edges of the graph
	Line i+1 (i = 1, 2, ..., m): contains 2 integer u and v which are endpoints of an edge of the graph 
	The first block is terminated with a line containing #
	The second block are K graphs in the queries with the format:
	Line 1: contains 2 integer n and m which are the number of nodes and edges of the graph
	Line i+1 (i = 1, 2, ..., m): contains 2 integer u and v which are endpoints of an edge of the graph 


Output
Line k (k = 1, 2, ..., K): contains 1 if the graph hk is present in G, and contains 0, otherwise

Example
Input 
4
3 3
1 2
1 3
2 3
4 4
1 2
2 3
3 4
1 4
4 5
1 2
1 3
2 3
2 4
3 4
4 5
1 2
1 3
1 4
2 4
3 4
#
3
3 2
1 2
1 3
4 5
1 3
1 4
2 3
2 4
3 4
4 4
1 2
1 3
2 4
3 4

Output
0
1
1

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef unsigned long long ull;

ull mix(ull x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

struct Graph {
    int n, m;
    vector<vector<int>> adj;
    vector<char> loop;
    vector<ull> color;
    vector<int> order;
    ull sig;
};

Graph readGraph() {
    Graph g;
    int m;
    cin >> g.n >> m;
    g.adj.assign(g.n, {});
    g.loop.assign(g.n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u == v) {
            g.loop[u] = 1;
        } else {
            g.adj[u].push_back(v);
            g.adj[v].push_back(u);
        }
    }

    g.m = 0;
    for (int u = 0; u < g.n; u++) {
        sort(g.adj[u].begin(), g.adj[u].end());
        g.adj[u].erase(unique(g.adj[u].begin(), g.adj[u].end()), g.adj[u].end());
        g.m += g.adj[u].size() + 2 * g.loop[u];
    }

    g.color.resize(g.n);
    for (int u = 0; u < g.n; u++) g.color[u] = mix(g.adj[u].size() * 2 + g.loop[u]);
    int rounds = min(g.n, 8);
    vector<ull> next(g.n);
    for (int r = 0; r < rounds; r++) {
        for (int u = 0; u < g.n; u++) {
            ull sum = 0;
            for (int v : g.adj[u]) sum += mix(g.color[v]);
            next[u] = mix(g.color[u] ^ mix(sum));
        }
        g.color = next;
    }

    g.sig = mix(g.n) ^ mix(g.m + 1000000007ULL);
    ull sum = 0;
    for (int u = 0; u < g.n; u++) sum += mix(g.color[u]);
    g.sig = mix(g.sig + sum);

    vector<char> seen(g.n, 0);
    for (int s = 0; s < g.n; s++) {
        if (seen[s]) continue;
        seen[s] = 1;
        size_t head = g.order.size();
        g.order.push_back(s);
        while (head < g.order.size()) {
            int u = g.order[head++];
            for (int v : g.adj[u]) {
                if (!seen[v]) {
                    seen[v] = 1;
                    g.order.push_back(v);
                }
            }
        }
    }
    return g;
}

bool hasEdge(const Graph &g, int u, int v) {
    return binary_search(g.adj[u].begin(), g.adj[u].end(), v);
}

bool canMap(const Graph &a, const Graph &b, const vector<int> &f, const vector<int> &used, int u, int c) {
    if (a.color[u] != b.color[c] || used[c] != -1) return false;
    int cnt = 0;
    for (int v : a.adj[u]) {
        if (f[v] == -1) continue;
        if (!hasEdge(b, c, f[v])) return false;
        cnt++;
    }
    for (int v : b.adj[c]) {
        if (used[v] != -1) cnt--;
    }
    return cnt == 0;
}

bool match(const Graph &a, const Graph &b, vector<int> &f, vector<int> &used, int pos) {
    if (pos == a.n) return true;
    int u = a.order[pos];
    int parent = -1;
    for (int v : a.adj[u]) {
        if (f[v] != -1) {
            parent = v;
            break;
        }
    }
    int total = parent == -1 ? b.n : b.adj[f[parent]].size();
    for (int i = 0; i < total; i++) {
        int c = parent == -1 ? i : b.adj[f[parent]][i];
        if (!canMap(a, b, f, used, u, c)) continue;
        f[u] = c;
        used[c] = u;
        if (match(a, b, f, used, pos + 1)) return true;
        f[u] = -1;
        used[c] = -1;
    }
    return false;
}

bool isomorphic(const Graph &a, const Graph &b) {
    if (a.n != b.n || a.m != b.m) return false;
    vector<int> f(a.n, -1), used(a.n, -1);
    return match(a, b, f, used, 0);
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Graph> graphs;
    graphs.reserve(N);
    unordered_map<ull, vector<int>> groups;
    for (int i = 0; i < N; i++) {
        graphs.push_back(readGraph());
        vector<int> &group = groups[graphs[i].sig];
        bool dup = false;
        for (int j : group) {
            if (isomorphic(graphs[j], graphs[i])) {
                dup = true;
                break;
            }
        }
        if (!dup) group.push_back(i);
    }

    string sep;
    cin >> sep;
    int K;
    cin >> K;
    while (K--) {
        Graph h = readGraph();
        bool found = false;
        auto it = groups.find(h.sig);
        if (it != groups.end()) {
            for (int j : it->second) {
                if (isomorphic(graphs[j], h)) {
                    found = true;
                    break;
                }
            }
        }
        cout << (found ? 1 : 0) << '\n';
    }

    return 0;
}
