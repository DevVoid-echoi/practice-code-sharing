#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!getline(cin, s)) {
        cout << "NOT_CORRECT\n";
        return 0;
    }

    const long long MOD = 1e9 + 7;
    long long Q = 0;
    long long current_num = 0;

    bool expecting_operand = true; 
    bool has_number = false;       
    bool has_at_least_one_number = false;

    for (char c : s) {
        if (c == ' ') {
            continue;
        } 
        else if (c >= '0' && c <= '9') {
            current_num = (current_num * 10 + (c - '0')) % MOD;
            has_number = true;
            expecting_operand = false; 
            has_at_least_one_number = true;
        } 
        else if (c == '+') {
            if (expecting_operand || !has_number) {
                cout << "NOT_CORRECT\n";
                return 0;
            }
            Q = (Q + current_num) % MOD;
            current_num = 0;
            has_number = false;
            expecting_operand = true;
        } 
        else {
            cout << "NOT_CORRECT\n";
            return 0;
        }
    }

    if (expecting_operand || !has_at_least_one_number) {
        cout << "NOT_CORRECT\n";
        return 0;
    }

    Q = (Q + current_num) % MOD;

    cout << Q << "\n";

    return 0;
}