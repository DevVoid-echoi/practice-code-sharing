#include <iostream>
#include <iomanip>

using namespace std;

double Current_option (int n) {
    double price;
    if (n>= 0 && n<=50) {
        price = n * 1728;
    }
    else if (n>= 51 && n<=100) {
        price = 50 * 1728 + (n-50) * 1786;
    }
    else if (n>= 101 && n<=200) {
        price = 50 * 1728 + 50 * 1786 + (n-100) * 2074;
    }
    else if (n>= 201 && n<=300) {
        price = 50 * 1728 + 50 * 1786 + 100 * 2074 + (n-200) * 2612;
    }
    else if (n>= 301 && n<=400) {
        price = 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + (n-300) * 2919;
    }
    else if (n>= 401) {
        price = 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + 100 * 2919 + (n-400) * 3015;
    }
    
    return price;
}

double New_option (int n) {
    double price;
    if (n>= 0 && n<=100) {
        price = n * 1728;
    }
    else if (n>= 101 && n<=200) {
        price = 100 * 1728 + (n-100) * 2074;
    }
    else if (n>= 201 && n<=400) {
        price = 100 * 1728 + 100 * 2074 + (n-200) * 2612;
    }
    else if (n>= 401 && n<=700) {
        price = 100 * 1728 + 100 * 2074 + 200 * 2612 + (n-400) * 3111;
    }
    else if (n>= 701) {
        price = 100 * 1.728 + 100 * 2.074 + 200 * 2.612 + 300 * 3.111 + (n-700) * 3.457;
    }
    
    return price;
}
int main () {
    int n;
    cin >> n;
    double current_price = Current_option(n);
    double new_price = New_option(n);

    double difference = (new_price - current_price) * 0.1;
    cout << difference;

    return 0;
}