/* Mỗi nút trên cây có trường id (identifier) là một số nguyên (id của các nút trên cây đôi một khác nhau)
Thực hiện 1 chuỗi các hành động sau đây bao gồm các thao tác liên quan đến xây dựng cây và duyệt cây
· MakeRoot u: Tạo ra nút gốc u của cây
· Insert u v: tạo mới 1 nút u và chèn vào cuối danh sách nút con của nút v (nếu nút có id bằng v không tồn tại hoặc nút có id bằng u đã tồn tại thì không chèn thêm mới)
· PreOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự trước
· InOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự giữa
· PostOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự sau
Dữ liệu: bao gồm các dòng, mỗi dòng là 1 trong số các hành động được mô tả ở trên, dòng cuối dùng là * (đánh dấu sự kết thúc của dữ liệu).
Kết quả: ghi ra trên mỗi dòng, thứ tự các nút được thăm trong phép duyệt theo thứ tự trước, giữa, sau của các hành động PreOrder, InOrder, PostOrder tương ứng đọc được từ dữ liệu đầu vào
Ví dụ
Dữ liệu
MakeRoot 10
Insert 11 10
Insert 1 10
Insert 3 10
InOrder
Insert 5 11
Insert 4 11
Insert 8 3
PreOrder
Insert 2 3
Insert 7 3
Insert 6 4
Insert 9 4
InOrder
PostOrder
*
Kết quả
11 10 1 3
10 11 5 4 1 3 8
5 11 6 4 9 10 1 8 3 2 7
5 6 9 4 11 1 8 2 7 3 10 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    vector<Node*> children;

    Node(int x) : id(x) {}
};

unordered_map<int, Node*> mp;
Node *root = nullptr;

void makeRoot(int u) {
    root = new Node(u);
    mp.clear();
    mp[u] = root;
}

void insert(int u, int v) {
    if (root == nullptr || mp.count(v) == 0 || mp.count(u) != 0) return;
    Node *p = mp[v];
    Node *newNode = new Node(u);
    mp[u] = newNode;
    p->children.push_back(newNode);
}

void dfsPre(Node *x, vector<int> &res) {
    if (!x) return;
    res.push_back(x->id);
    for (Node *child : x->children) dfsPre(child, res);
}

void dfsIn(Node *x, vector<int> &res) {
    if (!x) return;
    if (!x->children.empty()) {
        dfsIn(x->children[0], res);
        res.push_back(x->id);
        for (int i = 1; i < (int)x->children.size(); ++i) {
            dfsIn(x->children[i], res);
        }
    } else {
        res.push_back(x->id);
    }
}

void dfsPost(Node *x, vector<int> &res) {
    if (!x) return;
    for (Node *child : x->children) dfsPost(child, res);
    res.push_back(x->id);
}

void printVec(const vector<int> &v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cmd;
    while (cin >> cmd && cmd != "*") {
        if (cmd == "MakeRoot") {
            int u; cin >> u;
            makeRoot(u);
        } else if (cmd == "Insert") {
            int u, v; cin >> u >> v;
            insert(u, v);
        } else if (cmd == "PreOrder") {
            vector<int> res;
            dfsPre(root, res);
            printVec(res);
        } else if (cmd == "InOrder") {
            vector<int> res;
            dfsIn(root, res);
            printVec(res);
        } else if (cmd == "PostOrder") {
            vector<int> res;
            dfsPost(root, res);
            printVec(res);
        }
    }

    return 0;
}

