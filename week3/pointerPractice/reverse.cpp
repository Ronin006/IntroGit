#include <iostream>
using namespace std;

int main() {
    char str[] = "Wasup my bois!";
    char* p = str;

    while (*p != '\0') {
        p++;
    }
    p--; //step back to last valid character

    cout << "Reversed string: ";
    while (p >= str) {
        cout << *p;
        p--;
    }
    cout << endl;

    return 0;
}
