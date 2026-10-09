/*
Given a BST initialized by NULL. Perform a sequence of operations on a BST including:
insert k: insert a key k into the BST (do not insert if the key k exists)
Input
•Each line contains command under the form: “insert k”
•The input is terminated by a line containing #
Output
•Write the sequence of keys of nodes visited by the pre-order traversal (separated by a SPACE character)
Example
Input
insert 20
insert 10
insert 26
insert 7
insert 15
insert 23
insert 30
insert 3
insert 8
#
Output
20 10 7 3 8 15 26 23 30
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    string cmd;
    while (cin >> cmd && cmd != "#") {
        int k;
        cin >> k;
        if (cmd != "insert") continue;
        if (!root) {
            root = new Node(k);
            continue;
        }
        Node *cur = root;
        while (true) {
            if (k == cur->key) break;
            if (k < cur->key) {
                if (!cur->left) { cur->left = new Node(k); break; }
                cur = cur->left;
            } else {
                if (!cur->right) { cur->right = new Node(k); break; }
                cur = cur->right;
            }
        }
    }

    stack<Node*> st;
    if (root) st.push(root);
    bool first = true;
    while (!st.empty()) {
        Node *cur = st.top();
        st.pop();
        if (!first) cout << ' ';
        cout << cur->key;
        first = false;
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
    cout << '\n';

    return 0;
}
