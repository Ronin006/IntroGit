#include <iostream>
#include <functional>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;


int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int apply(function<int(int, int)> func, int a, int b) {
    return func(a, b);
}

void myTransform(vector<int>& vec, function<int(int)> func) {
    for (int& i : vec) {
        i = func(i);
    }
}

int square(int x) { return pow(x, 2); }
int double_num(int x) { return 2 * x; }

void myForeach(vector<int> vec, function<void(int)> func) {
    for (int i : vec) func(i);
}

void print(int i) { cout << i << endl; }

bool any(vector<int> vec, function<bool(int)> func) {
    for (int x : vec) {
        if (func(x)) return true;
    }
    return false;
}

bool equals10(int x) { return x == 10; }
bool greaterthan100(int x) { return x > 100; }

vector<int> filter(vector<int> vec, function<bool(int)> func) {
    vector<int> result;
    for (int x : vec) {
        if (func(x)) result.push_back(x);
    }
    return result;
}

bool isEven(int x) { return x % 2 == 0; }

int until(int x, function<int(int)> f, function<bool(int)> g) {
    while (!g(x)) {
        x = f(x);
    }
    return x;
}


int main() {
 
    vector<int> vec;
    for (int i = 0; i <= 10; i++) {
        vec.push_back(i);
    }

    vec = filter(vec, isEven);
    myForeach(vec, print);

    cout << "Any equals 10: " << any(vec, equals10) << endl;
    cout << "Any > 100: " << any(vec, greaterthan100) << endl;

   
    assert(until(1, double_num, greaterthan100) == 128);
    assert(until(10, [](int v){ return v - 1; }, equals10) == 10);
    assert(until(3, double_num, [](int v){ return v > 20; }) == 24);

    cout << "All until tests passed successfully!\n";
}