/*
A database contains a sequence of key k1, k2, ..., kn which are strings (1<=n<=100000). Perform a sequence of actions of two kinds:
· find k: find and return 1 if k exists in the database, and return 0, otherwise
· insert k: insert a key k into the database and return 1 if the insertion is successful (k does not exist in the database) and return 0 if the insertion is failed (k exists in the database)
Note that the length of any key is greater than 0 and less than or equal to 50.
Input
Two blocks of information. The first block contains a key of (k1,k2,...,kn) in each line. The first block is terminated with a line containing *. The second block is a sequence of actions of two finds described above: each line contains 2 string: cmd and k in which cmd = find or insert and k is the key (parameter of the action). The second block is terminated with a line containing ***. Note that the number of actions can be up to 100000.
Output
Each line contains the result (0 or 1) of the corresponding action.
Example
Input
computer
university
school
technology
phone
*
find school
find book
insert book
find algorithm
find book
insert book
***
Output
1
0
1
0
1
0
*/
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_set<string> db;
    db.reserve(400000);
    string s;
    while (cin >> s && s != "*") db.insert(s);

    string cmd, k;
    while (cin >> cmd && cmd != "***") {
        cin >> k;
        if (cmd == "find") cout << (db.count(k) ? 1 : 0) << '\n';
        else cout << (db.insert(k).second ? 1 : 0) << '\n';
    }

    return 0;
}
