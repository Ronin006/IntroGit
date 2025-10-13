#include <iostream>

using namespace std;

template<class T>
void print(T a){
    cout << a << endl;
}

template<class T>
T max_two(T a, T b){
    if(a > b){ return a;}
    return b;
}

template<class T>
T max_three(T a, T b, T c){
    if(a > b && a > c) {return a;}
    if(b > a && b > c) {return b;}
    return c;
    
}

template<class T>
void swapT(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

int main(){
    int a = 5;
    int b = 4;
    int c = 7;
    print(max_two(a, b));
    print(max_three(a, b, c));
    swapT(a, c);
    print(a);
    print(c);


}