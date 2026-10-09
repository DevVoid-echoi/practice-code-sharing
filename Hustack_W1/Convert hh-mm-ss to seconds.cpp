#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    
    if (s.size() != 8) {
        cout << "INCORRECT";
        return 0;
    }

    if (s[2] != ':' || s[5] != ':') {
        cout << "INCORRECT";
        return 0;
    }

    for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5) continue;
        if (s[i] < '0' || s[i] > '9') {
            cout << "INCORRECT";
            return 0;
        }
    }

    int hh = (s[0] - '0') * 10 + (s[1] - '0');
    int mm = (s[3] - '0') * 10 + (s[4] - '0');
    int ss = (s[6] - '0') * 10 + (s[7] - '0');

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59) {
        cout << "INCORRECT";
        return 0;
    }

    cout << hh * 3600 + mm * 60 + ss;
    return 0;
}    