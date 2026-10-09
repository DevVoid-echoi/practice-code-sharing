/*
Given a family tree represented by child-parent (c,p) relations in which c is a child of p. Perform queries about the family tree:
descendants <name>: return number of descendants of the given <name>
generation <name>: return the number of generations of the descendants of the given <name>

Note that: the total number of people in the family is less than or equal to 10
4
Input
Contains two blocks. The first block contains information about child-parent, including lines (terminated by a line containing ***), each line contains: <child> <parent> where <child> is a string represented the name of the child and <parent> is a string represented the name of the parent. The second block contains lines (terminated by a line containing ***), each line contains two string <cmd> and <param> where <cmd> is the command (which can be descendants or generation) and <param> is the given name of the person participating in the  query.
Output
Each line is the result of a corresponding query.
Example
Input
Peter Newman
Michael Thomas
John David
Paul Mark
Stephan Mark
Pierre Thomas
Mark Newman
Bill David
David Newman
Thomas Mark
***
descendants Newman
descendants Mark
descendants David
generation Mark
***
Output
10
5
2
2
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> id;
vector<vector<int>> children;

int getId(const string &name) {
    auto it = id.find(name);
    if (it != id.end()) return it->second;
    int k = children.size();
    id[name] = k;
    children.push_back({});
    return k;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    while (cin >> a && a != "***") {
        cin >> b;
        int c = getId(a), p = getId(b);
        children[p].push_back(c);
    }

    while (cin >> a && a != "***") {
        cin >> b;
        auto it = id.find(b);
        if (it == id.end()) {
            cout << 0 << '\n';
            continue;
        }
        vector<pair<int, int>> st;
        st.push_back({it->second, 0});
        int cnt = 0, maxDepth = 0;
        while (!st.empty()) {
            auto [u, d] = st.back();
            st.pop_back();
            if (d > maxDepth) maxDepth = d;
            for (int v : children[u]) {
                cnt++;
                st.push_back({v, d + 1});
            }
        }
        if (a == "descendants") cout << cnt << '\n';
        else cout << maxDepth << '\n';
    }

    return 0;
}
