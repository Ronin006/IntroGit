#include <iostream>
#include <cctype>
using namespace std;

static char board[3][3];
static char currP  = 'X';   
static int  player = 1;    
static bool ended  = false;

void printBoard(){
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "----------" << endl;
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "----------" << endl;
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool checkWinner(char p){
    for(int i=0;i<3;i++){//rows
        if(board[i][0]==p && board[i][1]==p && board[i][2]==p){
            return true;
        }
    }
    for(int j=0;j<3;j++){//cols
        if(board[0][j]==p && board[1][j]==p && board[2][j]==p){
            return true;
        }
    }
    //diags
    if(board[0][0]==p && board[1][1]==p && board[2][2]==p) return true;
    if(board[0][2]==p && board[1][1]==p && board[2][0]==p) return true;
    return false;
}

void switchPlayers(){
    if(currP=='X'){
        currP='O';
        player=2;
    }else{
        currP='X';
        player=1;
    }
}

void tictac(){
    int moves = 0; //count VALID moves only

    while(!ended && moves < 9){
        printBoard();
        cout << "Player " << player << " (" << currP << ") make your move (1-9): " << endl;

        int move;
        if(!(cin >> move)){
            cin.clear();              
            cin.ignore(10000, '\n');   
            cout << "Please enter a NUMBER from 1 to 9." << endl;
            continue;                  
        }

        //range check
        if(move < 1 || move > 9){
            cout << "Please enter a number from 1 to 9." << endl;
            continue;
        }

        int r = (move-1)/3;
        int c = (move-1)%3;

        //occupied check
        if(board[r][c]=='X' || board[r][c]=='O'){
            cout << "That tile is already taken. Choose another." << endl;
            continue;
        }

        //place mark
        board[r][c] = currP;
        moves = moves + 1;

        //win?
        if(checkWinner(currP)){
            printBoard();
            cout << "Player " << player << " (" << currP << ") wins!" << endl;
            ended = true;
            break;
        }

        //tie?
        if(moves == 9){
            printBoard();
            cout << "It's a tie!" << endl;
            ended = true;
            break;
        }

        switchPlayers();
    }
}

int main(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j] = char('1' + (i*3 + j));
        }
    }

    cout << "It's a tic-tac-toe game. Player 1 is X and Player 2 is O. Player 1 starts first." << endl;
    cout << "Type 1-9 as input to mark the corresponding tile." << endl;

    tictac();
    return 0;
}