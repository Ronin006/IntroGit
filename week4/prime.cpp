#include <iostream>
#include <vector>
using namespace std;

static int f = 2;
static vector<int> factors;

void prime(int n){

    if(n<=1) return;

    if(n % f == 0){ 
        factors.push_back(f);
        prime(n/f);
            //f = 2 not working
    }else{
        f++;
        prime(n);
    }
}

void reset(){
    for(int i : factors){
        cout << i << ", ";  
    }
    cout << endl;
    f=2;
    factors.clear();
}

int main() {

    prime(100);
    reset();
    
    prime(235);
    reset();

    prime(0);
    reset();

    return 0;
}