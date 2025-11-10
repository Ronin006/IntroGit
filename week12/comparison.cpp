#include <iostream>

using namespace std;

class Number {
private:
    int x;

public:
    Number(int a) {
        x = a;
    }

    Number operator+(const Number& y) {
        return Number(this->x + y.x);
    }

    void operator+=(const Number& y) {
        this->x += y.x;
    }

    int get_x() {
        return x;
    }
};

class ComplexNumber {
public:
    int real;
    int im;

    ComplexNumber(int x, int y) {
        real = x;
        im = y;
    }

    ComplexNumber operator+(const ComplexNumber& num) {
        return ComplexNumber(real + num.real, im + num.im);
    }

    ComplexNumber operator-(const ComplexNumber& num) {
        return ComplexNumber(real - num.real, im - num.im);
    }

    ComplexNumber operator*(const ComplexNumber& num) {
        return ComplexNumber(real * num.real - im * num.im, real * num.im + num.real * im);
    }

    bool operator<(const ComplexNumber& num) const {
        if (real < num.real) {
            return true;
        } else if (real == num.real) {
            return im < num.im;
        } else {
            return false;
        }
    }

    //added comparisons
    bool operator==(const ComplexNumber& num) const {
        return real == num.real && im == num.im;
    }

    bool operator!=(const ComplexNumber& num) const {
        return !(*this == num);
    }

    bool operator>(const ComplexNumber& num) const {
        return num < *this;
    }

    bool operator<=(const ComplexNumber& num) const {
        return !(*this > num);
    }

    bool operator>=(const ComplexNumber& num) const {
        return !(*this < num);
    }

    void pretty_print() const {
        cout << real << " + " << im << "i" << endl;
    }
};

int main() {
    ComplexNumber x = ComplexNumber(1, 2);
    ComplexNumber x2 = ComplexNumber(1, 3);
    ComplexNumber x3 = ComplexNumber(1, 1);
    ComplexNumber y = ComplexNumber(5, 8);
    ComplexNumber z = ComplexNumber(0, 1);

    cout << (x < y) << endl;
    cout << (x < x2) << endl;
    cout << (x < x3) << endl;

    //tests
    cout << (x == ComplexNumber(1, 2)) << endl;
    cout << (x != x2) << endl;
    cout << (x > x3) << endl;
    cout << (x <= x2) << endl;
    cout << (x >= x3) << endl;

    x.pretty_print();
    (x * z).pretty_print();
    (x * z * z).pretty_print();
    (x * z * z * z).pretty_print();

    return 0;
}