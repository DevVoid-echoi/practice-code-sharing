/*
Given a undirected connected graph G=(V,E) where V={1,…,N}. Each edge (u,v)∈E(u,v)∈E has weight w(u,v)w(u,v). Compute minimum spanning tree of G.
Input
Line 1: N and M (1≤N,M≤10
5
) in which NN is the number of nodes and MM is the number of edges.
Line i+1 (i=1,…,M): contains 3 positive integers u, v, and w where w is the weight of edge (u,v)
Output
Write the weight of the minimum spanning tree found.
Example
Input
5 8
1 2 1
1 3 4
1 5 1
2 4 2
2 5 1
3 4 3
3 5 3
4 5 2
Output
7
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

using namespace std;

vector<int> parent_, rank_;

int find(int x) {
    while (parent_[x] != x) {
        parent_[x] = parent_[parent_[x]];
        x = parent_[x];
    }
    return x;
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (rank_[a] < rank_[b]) swap(a, b);
    parent_[b] = a;
    if (rank_[a] == rank_[b]) rank_[a]++;
    return true;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> edges(m);
    for (auto &e : edges) cin >> e[1] >> e[2] >> e[0];
    sort(edges.begin(), edges.end());

    parent_.resize(n + 1);
    rank_.assign(n + 1, 0);
    iota(parent_.begin(), parent_.end(), 0);

    long long total = 0;
    int cnt = 0;
    for (auto &e : edges) {
        if (unite(e[1], e[2])) {
            total += e[0];
            if (++cnt == n - 1) break;
        }
    }
    cout << total << '\n';

    return 0;
}
