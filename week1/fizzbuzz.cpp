#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

string fizzbuzz(int n) {
  if(n % 3 == 0 && n % 5 == 0) {
    return "fizzbuzz";
  } else if (n % 3 == 0) {
    return "fizz";
  } else if (n % 5 == 0) {
    return "buzz";
  } else {
    return to_string(n);
  }
}
int main() {
    for(int i = 1; i <= 15; i++){
        std::cout << "The output for " << i << "is: " + fizzbuzz(i)<< std::endl;
    }
    
    return 0;
    
}