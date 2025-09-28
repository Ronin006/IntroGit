#include <iostream>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;


class Shape{
    protected:
        string name;
    public:

        virtual double getArea()=0;
        virtual double getPerimeter()=0;

        string getName(){
            return name;
        }

};

class Rectangle : public Shape{
    double b, h;

    public:

        Rectangle(double base, double height){
            b = base;
            h = height;
            name = "Rectangle";
        }
        double getArea(){
            return b * h;
        }
        double getPerimeter(){
            return 2 * (b + h);
        }

};

class Square : public Rectangle{
    public:

        Square(double base) : Rectangle(base, base){
            name = "Square";
        }


};

class Circle : public Shape{
    double r;

    public:

        Circle(double radius){
           r=radius;
           name = "Circle";
        }

        double getArea(){
           return (M_PI) * pow(r, 2);
        }
        double getPerimeter(){
           return 2 * (M_PI) * r;
        }

};

class RightTriangle : public Shape{
    double b, h;

    public:
        RightTriangle(double base, double height){
            b = base;
            h = height;
            name = "Right Triangle";
        }

        double getArea(){
            return 0.5 * b * h;

        }
        double getPerimeter(){
            return b + h + sqrt(pow(b, 2) + pow(h, 2));
    
        }
};

class IsocelesRightTriangle : public RightTriangle{
    
    public:
        IsocelesRightTriangle(double base) : RightTriangle(base, base){
            name = "Isoceles Right Triangle";
        }

};

void printAreaToScreen(Shape *s){
    cout << "The area of the " << s->getName() << " is " << s->getArea() << endl;
}


int main(){
    Circle c(3);
    printAreaToScreen(&c);
    cout << c.getPerimeter() << endl;

    RightTriangle t(2, 5);
    printAreaToScreen(&t);
    cout << t.getPerimeter() << endl;

    Rectangle r(4, 5);
    printAreaToScreen(&r);
    cout << r.getPerimeter() << endl;

    Square s(4);
    printAreaToScreen(&s);
    cout << s.getPerimeter() << endl;

    IsocelesRightTriangle i(3);
    printAreaToScreen(&i);
    cout << i.getPerimeter() << endl;
    

    return 0;
}