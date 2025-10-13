#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>


using namespace std;

template <class T>
vector<T> vec_fill(T elem){
    vector<T> v;
    for(int i = 0; i < 10; i++){
        v.push_back(elem + i);
    }
    return v;
}

template <class T>
T until(T elem, function<T(T)> func, function<bool(T)> predicate) {
    while (!predicate(elem)) {
        elem = func(elem);
    }
    return elem;
}

template <class T>
void order(T& a, T& b, T& c){
    if(a < b) swap(a, b);
    if(a < c) swap(a, c);
    if(b < c) swap(b, c);

}

int main(){

    //vec_fill
    auto v1 = vec_fill(1);
    assert(v1[0] == 1 && v1[9] == 10);

    auto v2 = vec_fill(2.5);
    assert(v2[0] == 2.5 && v2[1] == 3.5);

    auto v3 = vec_fill('a');
    assert(v3[0] == 'a' && v3[1] == 'b');

    //until
    int x = until<int>(1, [](int n){ return n * 2; }, [](int n){ return n > 10; });
    assert(x == 16);

    double y = until<double>(1.0, [](double n){ return n + 1.5; }, [](double n){ return n > 4.0; });
    
    assert(y == 5.5);

    char c = until<char>('a', [](char ch){ return ch + 1; }, [](char ch){ return ch == 'd'; });
    assert(c == 'd');

    //order
    int a = 3, b = 1, c1 = 2;
    order(a, b, c1);
    assert(a == 3 && b == 2 && c1 == 1);

    double da = 5.5, db = 9.1, dc = 7.2;
    order(da, db, dc);
    assert(da == 9.1 && db == 7.2 && dc == 5.5);

    char ca = 'x', cb = 'z', cc = 'a';
    order(ca, cb, cc);
    assert(ca == 'z' && cb == 'x' && cc == 'a');

    return 0;
}