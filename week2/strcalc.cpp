#include <cassert>
#include <string>
 
using namespace std;
 
int string_calculator(string str) {
	// Your code goes here
    if (str.empty()) return 0;

    int sum = 0;
    int current = 0;
    bool inNumber = false;

    for (char c : str) {
        if (isdigit(c)) {
            current = current * 10 + (c - '0');
            inNumber = true;
        } else if (c == ',' || c == ';') {
            if (inNumber) {
                sum += current;
                current = 0;
                inNumber = false;
            }
        }
    }

    if (inNumber) {
        sum += current;
    }

    return sum;

}
 
int main() {
	assert(string_calculator("") == 0);
	assert(string_calculator("0") == 0);
	assert(string_calculator("1") == 1);
	assert(string_calculator("1,2") == 3);
	assert(string_calculator("4,5,6") == 15);
	
    assert(string_calculator("1;2;3") == 6);
    assert(string_calculator("10;20,30") == 60);

    assert(string_calculator("7,8;9") == 24);
    assert(string_calculator("100") == 100);
	// And so on with more examples...
}