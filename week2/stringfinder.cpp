#include <iostream>
#include <assert.h>
#include <cctype> 

int find (const std::string text, char str) {
    for(int i = 0; i < text.length(); i++) {
        if (text[i] == str) {
            return i; // Convert char digit to int
        }
    }
    return -1; // Only return -1 if not found after checking all characters
}

int find(const std::string text, const std::string str){
    for(int i = 0; i <= text.length() - str.length(); i++) {
        if (text.substr(i, str.length()) == str) {
            return i;
        }
    }
    return -1; // Only return -1 if not found after checking all characters
}

int main(){
    assert(find("hello", 'e') == 1);
    assert(find("hello", 'l') == 2);
    assert(find("hello", 'a') == -1);
    assert(find("hello", "ll") == 2);
    assert(find("hello", "lo") == 3);
    assert(find("hello", "world") == -1);
    return 0;
}