#include <iostream>
using namespace std;

int main() {
    char str[] = "Hello, world!";
    char* p = str;
    int length = 0;

    while (*p != '\0') {
        length++;
        p++;
    }

    cout << "Length of string: " << length << endl;
    return 0;
}
