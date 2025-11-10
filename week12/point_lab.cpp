#include <iostream>
#include <cmath>
#include <stdexcept> 

using namespace std;

class Point {
private:
    double x;
    double y;

public:
    Point(double x_val = 0, double y_val = 0) {
        x = x_val;
        y = y_val;
    }

    double operator-(const Point& other) const {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    //check if two points are equal
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    //check if two points are not equal
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    //midpoint
    Point operator/(const Point& other) const {
        return Point((x + other.x) / 2.0, (y + other.y) / 2.0);
    }

    //output streaming
    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }

    //input streaming
    friend istream& operator>>(istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

    Point& operator++() {
        ++x;
        return *this;
    }

    Point operator++(int) {
        Point temp = *this;
        y++;
        return temp;
    }

    Point& operator--() {
        --x;
        return *this;
    }

    Point operator--(int) {
        Point temp = *this;
        y--;
        return temp;
    }

    //access coordinates
    double& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else throw out_of_range("Index must be 0 for x or 1 for y");
    }
};

int main() {
    Point p1(2, 3), p2(4, 7);

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    cout << "Distance: " << (p2 - p1) << endl;
    cout << "Midpoint: " << (p1 / p2) << endl;

    ++p1; 
    p2++; 
    cout << "After increments: p1=" << p1 << ", p2=" << p2 << endl;

    --p1; 
    p2--; 
    cout << "After decrements: p1=" << p1 << ", p2=" << p2 << endl;

    cout << "Access using [] -> p1[0]=" << p1[0] << ", p1[1]=" << p1[1] << endl;

    Point p3;
    cout << "Enter coordinates for p3 (x y): ";
    cin >> p3;
    cout << "You entered p3 = " << p3 << endl;

    return 0;
}