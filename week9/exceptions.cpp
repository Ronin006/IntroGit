#include <iostream>
#include <exception>  

using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int index;

    cout << "Enter an index (0–4): ";
    cin >> index;

    try {
        if (index < 0 || index >= 5) {
            throw exception();
        }
        cout << "Value at index " << index << " is " << arr[index] << endl;
    }
    catch (const exception& e) {
        cerr << "Error: Index out of range!" << endl;
    }

    return 0;
}