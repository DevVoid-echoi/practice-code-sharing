#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string text;
    string line;
    while (getline(cin, line)) {
        text += line + "\n";
    }

    for (char &c : text) {
        c = toupper(c);
    }

    cout << text;
    return 0;
}