#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

int applyOp(int total, int value, char op) {
    if (op == '+') return total + value;
    if (op == '-') return total - value;
    if (op == '*') return total * value;
    return total;
}

int snakeCalc(vector<string> list, int r, int c, int total, char op){
    //base case
    if (r < 0 || r >= (int)list.size() || c >= (int)list[r].size())
        return total; 

    char ch = list[r][c];

    if (isdigit(ch)) {
        total = applyOp(total, ch - '0', op);
        return snakeCalc(list, r, c + 1, total, op);
    }
    else if (ch == '+' || ch == '-' || ch == '*') {
        return snakeCalc(list, r, c + 1, total, ch);
    }
    else if (ch == 'v') {
        // branch down, then return back and continue
        int branch = snakeCalc(list, r + 1, c, total, op);
        return snakeCalc(list, r, c + 1, branch, op);
    }
    else if (ch == '^') {
        int branch = snakeCalc(list, r - 1, c, total, op);
        return snakeCalc(list, r, c + 1, branch, op);
    }
    else {
        return snakeCalc(list, r, c + 1, total, op); // skip unknowns/spaces
    }
}

int main(){
    vector<string> arr = {
        "257*233+6v790-12", //[0][0]
        "61247833212+*9^3" //[0][1]
        };
    cout << snakeCalc(arr, 0, 0, 0, '+');

    return 0;
}