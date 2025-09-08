#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers \n";
    cout << "First integer: \n";
    cin >> a;
    cout << "Second integer: \n";
    cin >> b;

    int* ptr_a = &a;
    int* ptr_b = &b;

    cout << "Value of a pointer: " << *ptr_a << endl;
    cout << "Value of b pointer: " << *ptr_b << endl;

    return 0;
}

