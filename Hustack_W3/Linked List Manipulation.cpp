/* Xây dựng danh sách liên kết với các khóa được cung cấp ban đầu là dãy a
1
, a
2
, …, a
n
, sau đó thực hiện các thao tác trên danh sách bao gồm: thêm 1 phần tử vào đầu, vào cuối danh sách, hoặc vào trước, vào sau 1 phần tử nào đó trong danh sách, hoặc loại bỏ 1 phần tử nào đó trong danh sách

Input
Dòng 1: ghi số nguyên dương n (1 <= n <= 1000)
Dòng 2: ghi các số nguyên dương a
1
, a
2
, …, a
n
.
Các dòng tiếp theo lần lượt là các lệnh để thao tác (kết thúc bởi ký hiệu #) với các loại sau:
addlast  k: thêm phần tử có key bằng k vào cuối danh sách (nếu k chưa tồn tại)
addfirst  k: thêm phần tử có key bằng k vào đầu danh sách (nếu k chưa tồn tại)
addafter  u  v: thêm phần tử có key bằng u vào sau phần tử có key bằng v trên danh sách (nếu v đã tồn tại trên danh sách và u chưa tồn tại)
addbefore  u  v: thêm phần tử có key bằng  u vào trước phần tử có key bằng v trên danh sách (nếu v đã tồn tại trên danh sách và u của tồn tại)
remove  k: loại bỏ phần tử có key bằng k khỏi danh sách
reverse: đảo ngược thứ tự các phần tử của danh sách (không được cấp phát mới các phần tử, chỉ được thay đổi mối nối liên kết)
Output
Ghi ra dãy khóa của danh sách thu được sau 1 chuỗi các lệnh thao tác đã cho

Example
Input
5
5 4 3 2 1
addlast 3
addlast 10
addfirst 1
addafter 10 4
remove 1
#

Output
5 4 3 2 10 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node *prev;
    Node *next;

    Node(int x) : key(x), prev(nullptr), next(nullptr) {}
};

class LinkedList {
private:
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    bool contains(int x) const {
        Node *cur = head;
        while (cur) {
            if (cur->key == x) return true;
            cur = cur->next;
        }
        return false;
    }

    void addFirst(int x) {
        if (contains(x)) return;
        Node *node = new Node(x);
        if (!head) {
            head = tail = node;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
    }

    void addLast(int x) {
        if (contains(x)) return;
        Node *node = new Node(x);
        if (!head) {
            head = tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    void addBefore(int u, int v) {
        if (contains(u) || !contains(v)) return;
        Node *target = head;
        while (target && target->key != v) target = target->next;
        if (!target) return;

        Node *node = new Node(u);
        if (target == head) {
            node->next = head;
            head->prev = node;
            head = node;
            return;
        }

        Node *before = target->prev;
        node->prev = before;
        node->next = target;
        target->prev = node;
        if (before) before->next = node;
    }

    void addAfter(int u, int v) {
        if (contains(u) || !contains(v)) return;
        Node *target = head;
        while (target && target->key != v) target = target->next;
        if (!target) return;

        Node *node = new Node(u);
        node->prev = target;
        node->next = target->next;
        if (target->next) target->next->prev = node;
        target->next = node;
        if (target == tail) tail = node;
    }

    void remove(int x) {
        Node *cur = head;
        while (cur && cur->key != x) cur = cur->next;
        if (!cur) return;

        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;

        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;

        delete cur;
    }

    void reverse() {
        if (!head || !head->next) return;

        Node *cur = head;
        while (cur) {
            Node *nextNode = cur->next;
            cur->next = cur->prev;
            cur->prev = nextNode;
            cur = nextNode;
        }

        swap(head, tail);
    }

    void print() const {
        Node *cur = head;
        bool first = true;
        while (cur) {
            if (!first) cout << ' ';
            cout << cur->key;
            first = false;
            cur = cur->next;
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    LinkedList list;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        list.addLast(x);
    }

    string cmd;
    while (cin >> cmd && cmd != "#") {
        if (cmd == "addlast") {
            int x;
            cin >> x;
            list.addLast(x);
        } else if (cmd == "addfirst") {
            int x;
            cin >> x;
            list.addFirst(x);
        } else if (cmd == "addafter") {
            int u, v;
            cin >> u >> v;
            list.addAfter(u, v);
        } else if (cmd == "addbefore") {
            int u, v;
            cin >> u >> v;
            list.addBefore(u, v);
        } else if (cmd == "remove") {
            int x;
            cin >> x;
            list.remove(x);
        } else if (cmd == "reverse") {
            list.reverse();
        }
    }

    list.print();
    return 0;
}

