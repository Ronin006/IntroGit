#include <iostream>
#include <vector>
using namespace std;

static int callCount = 0; 
static vector<long long> memo(100, -1);

int fibReccursion(int n){
    callCount++;
    if (n <= 0) return 0;
    if(n == 1 || n == 2){
        return 1;
    }else{
        return fibReccursion(n-1) + fibReccursion(n-2);
    }
}

int fibLoop(int n){
    callCount++;
    if(n <= 0) return 0;
    if(n == 1 || n == 2) return 1;
    int prev1 =1, prev2 =1;
    int result=0;
    for(int i=3; i<=n; i++){
        result = prev1 + prev2;
        prev2 = prev1;
        prev1 = result;
    }
    return result;
}

long long fibMemo(int n, vector<long long>& memo){
    callCount++;
    if(n==0) return 0;
    if(n==1 || n==2) return 1;

    if(memo[n] != -1) return memo[n];

    memo[n] = fibMemo(n-1, memo) + fibMemo(n-2, memo);
    return memo[n];
}

int main(){
    cout << fibReccursion(10) << endl;
    cout << callCount << endl;
    cout << fibLoop(10) << endl;
    cout << callCount << endl;
    cout << fibMemo(10, memo) << endl;
    cout << callCount << endl;
    
    return 0;
}
