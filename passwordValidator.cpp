#include <cassert>
#include <string>
#include <iostream>
#include <assert.h>
#include <cctype>
#include <_ctype.h>

using namespace std;
 
bool valid_password(string password) {
  int digit_count = 0;
  bool right= true;
  bool has_upper = false;
  bool has_special = false;
  bool has_space = false;
  // Your code goes here

  if (password.length() < 8) {
    std::cout << "The password must be at least 8 characters" << std::endl;
    right = false;
  }

  for(char c : password){
    if (std::isdigit(c)) {
      digit_count++;
    }
    if (std::isblank(c)) {
      has_space = true;
    }
    if (std::isupper(c)) {
      has_upper = true;
    }
    if (std::ispunct(c)) {
      has_special = true;
    } 
  }
    if (digit_count < 2) {
      std::cout << "The password must contain at least 2 digits" << std::endl;
      right = false;
    }
    
    if(has_space){
      std::cout << "The password shouldn't contain any spaces" << std::endl;
      right = false;
    }
    if(!has_upper){
      std::cout << "The password must contain at least 1 capital letter" << std::endl;
      right = false;
    }
    if(!has_special){
      std::cout << "The password must contain at least 1 special character" << std::endl;
      right = false;
    }
    return right; // Placeholder return value

}
 
int main() {
    
  assert(!valid_password("short"));
  assert(valid_password("020123Rr@"));
}