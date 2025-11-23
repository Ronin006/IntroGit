#include <iostream>
#include <vector>

using namespace std;

bool is_sorted(const vector<int>& vec){

    for(size_t i = 1; i < vec.size(); i++){
        if(vec[i-1] > vec[i]) return false;
    }
    return true;
}

bool subset_sum(const vector<int>& nums, const vector<size_t>& indices, int target) {

    long long sum = 0;
    for (size_t idx : indices) {
        if (idx >= nums.size()) return false; //invalid index
        sum += nums[idx];
    }
    return sum == target;
}

bool is_prime(int n) {

    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; 1LL * d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

bool is_prime_factorization(int n, const vector<int>& factors) {

    if (n <= 1) return false;

    long long product = 1;
    for (int f : factors) {
        if (!is_prime(f)) return false; //all must be prime
        product *= f;
        if (product > n) return false; //early exit if too big
    }
    return product == n;
}

int main(){

}