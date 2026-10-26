/*
Given a undirected graph =(V,E) in which V = {1,2,..,n} is the set of nodes. Write a program that visit nodes of G by a DFS (consider a lexicorgraphic order of nodes).
Input
Line 1: contains 2 integers n and m (1 <= n,m <= 100000)
Line i+1: contains u and v which are two end-points of the ith edge

Output
Sequence of nodes visited by DFS
Example
Input
7 12
1 2
1 3
2 3
2 4
2 7
3 5 
3 7
4 5
4 6
4 7
5 6
5 7 
Output
1 2 3 5 4 6 7
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());

    vector<bool> visited(n + 1, false);
    vector<int> idx(n + 1, 0);
    vector<int> st;
    for (int s = 1; s <= n; s++) {
        if (visited[s]) continue;
        visited[s] = true;
        cout << s << ' ';
        st.push_back(s);
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] == (int)adj[u].size()) {
                st.pop_back();
                continue;
            }
            int v = adj[u][idx[u]++];
            if (!visited[v]) {
                visited[v] = true;
                cout << v << ' ';
                st.push_back(v);
            }
        }
    }
    cout << '\n';

    return 0;
}
