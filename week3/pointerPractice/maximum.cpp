#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    const int SIZE = 10;
    int arr[SIZE];

    //fill with random values
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100; 
        cout << arr[i] << " ";
    }
    cout << endl;

    int* max_ptr = arr;  //point to first element
    for (int* p = arr; p < arr + SIZE; p++) {
        if (*p > *max_ptr) {
            max_ptr = p;
        }
    }

    cout << "Maximum value: " << *max_ptr << endl;
    return 0;
}
