#include <iostream>
#include <string>

using namespace std;

int main () {
    string text;
    string line;

    while (getline(cin, line)) {
        text += line + " ";
    }

    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ' && text[i-1] != ' ') {
            count++;
        }
    }
    cout << count;

    return 0;
}

