#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> vec = {3, 7, 12, 18, 25, 30, 42}; 

    int* left = &vec[0];
    int* right = &vec[vec.size() - 1];

    while (left < right) {
        left++;
        right--;
    }

    cout << "Midpoint value: " << *left << endl;
    return 0;
}
