//exGCD
#include <iostream>
using namespace std;

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = exgcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int a, b;
    cout << "Enter a and b: ";
    cin >> a >> b;

    int x, y;
    int g = exgcd(a, b, x, y);

    cout << "gcd(" << a << ", " << b << ") = " << g << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "Check: " << a << "*" << x << " + " << b << "*" << y << " = " << a*x + b*y << endl;

    return 0;
}
