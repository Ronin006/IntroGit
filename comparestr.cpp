#include <iostream>
#include <assert.h>
#include <cctype>

/*


int strcmp(const std::string& str1, const std::string& str2) {
    if (str1 == str2) {
        return 0; // Strings are equal
    } else if (str1 < str2) {
        return -1; // str1 is less than str2
    } else {
        return 1; // str1 is greater than str2
    }
}

*/

int strcmp_case_insensative(const std::string str1, const std::string str2) {
    std::string one;
    std::string two;
    for (char c : str1) {
        one += std::tolower(c);
    }
    for (char c : str2) {
        two += std::tolower(c);
    }
    if(one == two) {
        return 0; // Strings are equal
    } else if (one < two) {
        return -1; // str1 is less than str2
    } else {
        return 1; // str1 is greater than str2
    }
}

int main(){
    std::cout << strcmp_case_insensative("Hello", "hellow") << std::endl;
    assert(strcmp_case_insensative("Hello", "hellow") == -1);
    assert(strcmp_case_insensative("Hello", "hello") == 0);
    assert(strcmp_case_insensative("Hellow", "hello") == 1);
}
