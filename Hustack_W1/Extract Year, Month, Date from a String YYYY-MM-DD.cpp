#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;

    if (s.size() != 10) {
        cout << "INCORRECT";
        return 0;
    }

    if (s[4] != '-' || s[7] != '-') {
        cout << "INCORRECT";
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (s[i] < '0' || s[i] > '9') {
            cout << "INCORRECT";
            return 0;
        }
    }

    int year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
    int month = (s[5] - '0') * 10 + (s[6] - '0');
    int date = (s[8] - '0') * 10 + (s[9] - '0');

    if (month < 1 || month > 12 || date < 1 || date > 31) {
        cout << "INCORRECT";
        return 0;
    }

    cout << year << " " << month << " " << date;
    return 0;
}
