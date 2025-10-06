#include <iostream>
#include <vector>
#include <functional>

using namespace std;



int fold(vector<int> v, function<int(int, int)> f, size_t i = 0){
    if(v.empty()){return 0;}

    if (i == v.size() - 1) return v[i];
    return f(v[i], fold(v, f, i + 1));
}


int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    std::cout << "Sum = " << fold(nums, [](int a, int b){ return a + b; }) << endl;

    return 0;
}