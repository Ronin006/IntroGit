#include <iostream>
#include <string>
#include <functional>
#include <cassert>

using namespace std;

template <typename R, typename A1, typename A2>
class Operator {
private:
    function<R(A1, A2)> func;
    size_t timesApplied = 0;
    bool hasPrev = false;
    R prevResult{}; 
public:
    Operator(function<R(A1, A2)> f) : func(f) {}

    R apply(A1 a, A2 b) {
        R r = func(a, b);
        ++timesApplied;
        prevResult = r;
        hasPrev = true;
        return r;
    }

    size_t count() const { return timesApplied; }
    bool hasPrevious() const { return hasPrev; }
    const R& previous() const {
        return prevResult;
    }


};


int main() {

    Operator<int, int, int> add([](int a, int b){ return a + b; });
    assert(add.apply(2, 3) == 5);
    assert(add.count() == 1);
    assert(add.previous() == 5);

    Operator<double, double, double> mul([](double a, double b){ return a * b; });
    assert(mul.apply(2.5, 4.0) == 10.0);
    assert(mul.count() == 1);

    cout << "All tests passed." << endl;
}