#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main () {
    int a, b, c;
    cin >> a >> b >> c;
    int delta = b * b - 4 * a * c;
    if (delta < 0) {
        cout << "NO SOLUTION";
    }
    else if (delta == 0) {
        double x = -b / (2.00 * a);
        cout << fixed << setprecision(2) << x;
    }
    else if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2.00 * a);
        double x2 = (-b - sqrt(delta)) / (2.00 * a);
        if (x1 > x2) {
            cout << fixed << setprecision(2) << x2 << " " << x1;
        }
        else {
            cout << fixed << setprecision(2) << x1 << " " << x2;
        }
    }

    return 0;
}