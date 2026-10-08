/*
Cho văn bản T và 2 mẫu P1, P2 đều là các xâu ký tự (không chứa ký tự xuống dòng, độ dài không vượt quá 1000). Hãy thay thế các xâu P1 trong T bằng xâu P2.
Dữ liệu
· Dòng 1: xâu P1
· Dòng 2: xâu P2
· Dòng 3: văn bản T
Kết quả:
· Ghi văn bản T sau khi thay thế
Ví dụ
Dữ liệu
AI
Artificial Intelligence
Recently, AI is a key technology. AI enable efficient operations in many fields.
Kết quả
Recently, Artificial Intelligence is a key technology. Artificial Intelligence enable efficient operations in many fields.
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    string p1, p2, t;
    getline(cin, p1);
    getline(cin, p2);
    getline(cin, t);

    size_t pos = 0;
    while ((pos = t.find(p1, pos)) != string :: npos) {
        t.replace(pos, p1.length(), p2);
        pos += p2.length();
    }

    cout << t << '\n';
    return 0;
}