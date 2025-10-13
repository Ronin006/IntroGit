#include <iostream>
#include <vector>


using namespace std;

template <class T>
class Stack {
private:
    vector<T> data;
public:

    void push(T a){
        data.push_back(a);
    }

	T pop(){
        int temp = data.back();
        data.pop_back();
        return temp;
    }

    T empty(){
        return data.empty();
    }

    T size(){
        return data.size();
    }
		
};

template <class T>
void print(T a){
    cout << a << endl;
}

int main() {
    Stack<int> s;

    s.push(3);
    s.push(6);
    s.push(4);
    
    print(s.pop());

    return 0;
}