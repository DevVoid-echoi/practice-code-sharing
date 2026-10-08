#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(){
    string input;
    string text;

    while (getline(cin, input)){
        text += input + "\n";
    }

    for (char& c: text){
        c = toupper(c);
    } 
    cout << text << endl;
}