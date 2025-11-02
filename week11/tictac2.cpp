#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char board[3][3];
int  player = 1;                    
char markOf[3] = {'?', 'X', 'O'};   //marks for players 1 and 2
int  archOf[3] = {0, 1, 1};         //1 paladin, 2 alchemist
bool ended = false;    //game ended

void resetBoard() {
    int n = 1;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            board[r][c] = char('0' + n);
            n++;
        }
    }
    player = 1;
    ended = false;
}

void printBoard() {
    cout << endl;
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << endl;
}

bool isOccupied(int r, int c) {
    return board[r][c] != char('1' + (r*3 + c));
}

void cellToRC(int cell, int &r, int &c) {
    r = (cell - 1) / 3;
    c = (cell - 1) % 3;
}

bool checkWinner(char m) {
    //rows
    for (int r = 0; r < 3; r++)
        if (board[r][0] == m && board[r][1] == m && board[r][2] == m) return true;
    //cols
    for (int c = 0; c < 3; c++)
        if (board[0][c] == m && board[1][c] == m && board[2][c] == m) return true;
    //diags
    if (board[0][0] == m && board[1][1] == m && board[2][2] == m) return true;
    if (board[0][2] == m && board[1][1] == m && board[2][0] == m) return true;
    return false;
}

void switchPlayer() {
    player = (player == 1 ? 2 : 1);
}

bool validMark(char ch) {
    if (isalpha((unsigned char)ch)) return true;
    if (ch=='?' || ch=='!' || ch=='*' || ch=='~' || ch=='$' || ch=='%' || ch=='#') return true;
    return false;
}

int askInt(const char* prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a number." << endl;
    }
}

char askChar(const char* prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (cin >> s) {
            if (s.size() == 1) return s[0];
            cout << "Enter exactly ONE character." << endl;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int openingMenu() {
    while (true) {
        cout << "========== TIC-TAC-TOE ==========" << endl;
        cout << "1) Regular" << endl;
        cout << "2) Battle" << endl;
        int choice = askInt("Choose (1 or 2): ");
        if (choice == 1 || choice == 2) return choice;
        cout << "Choose 1 or 2." << endl;
    }
}

bool playAgainMenu() {
    while (true) {
        char ch = askChar("Play again? (y/n): ");
        ch = (char)tolower((unsigned char)ch);
        if (ch == 'y') return true;
        if (ch == 'n') return false;
        cout << "Please enter y or n." << endl;
    }
}

void setupRegular() {
    markOf[1] = 'X';
    markOf[2] = 'O';
}

void setupBattle() {
    //marks
    while (true) {
        markOf[1] = askChar("Player 1, choose your mark (A-Z, a-z, or one of ? ! * ~ $ % #): ");
        if (!validMark(markOf[1]) || isdigit((unsigned char)markOf[1])) {
            cout << "Invalid. Try again." << endl;
            continue;
        }
        break;
    }
    while (true) {
        markOf[2] = askChar("Player 2, choose your mark (A-Z, a-z, or one of ? ! * ~ $ % #): ");
        if (!validMark(markOf[2]) || isdigit((unsigned char)markOf[2])) {
            cout << "Invalid. Try again." << endl;
            continue;
        }
        if (markOf[2] == markOf[1]) {
            cout << "That mark is taken by Player 1. Pick a different mark." << endl;
            continue;
        }
        break;
    }

    //archetypes (1=Paladin, 2=Alchemist)
    while (true) {
        cout << "Player 1 archetype:" << endl;
        cout << "  1) Paladin (shift a mark to an adjacent empty cell)" << endl;
        cout << "  2) Alchemist (swap two existing marks)" << endl;
        int a = askInt("Choose 1 or 2: ");
        if (a == 1 || a == 2) { archOf[1] = a; break; }
        cout << "Choose 1 or 2." << endl;
    }
    while (true) {
        cout << "Player 2 archetype:" << endl;
        cout << "  1) Paladin (shift a mark to an adjacent empty cell)" << endl;
        cout << "  2) Alchemist (swap two existing marks)" << endl;
        int a = askInt("Choose 1 or 2: ");
        if (a == 1 || a == 2) { archOf[2] = a; break; }
        cout << "Choose 1 or 2." << endl;
    }
}

bool isAdjacentCell(int fromCell, int toCell) {
    int r1, c1, r2, c2;
    cellToRC(fromCell, r1, c1);
    cellToRC(toCell, r2, c2);
    int dr = r2 - r1;
    int dc = c2 - c1;
    if (dr == 0 && dc == 0) return false;
    if (dr >= -1 && dr <= 1 && dc >= -1 && dc <= 1) return true;
    return false;
}

//regular mode
void playRegular() {
    resetBoard();
    int moves = 0;

    cout << "Regular mode: Player 1 is " << markOf[1] << ", Player 2 is " << markOf[2] << ". Player 1 starts." << endl;

    while (!ended && moves < 9) {
        printBoard();
        string prompt = string("Player ") + to_string(player) + " (" + markOf[player] + ") enter a move (1-9): ";
        int cell = askInt(prompt.c_str());
        if (cell < 1 || cell > 9) { cout << "Choose 1..9." << endl; continue; }
        int r, c; cellToRC(cell, r, c);
        if (isOccupied(r, c)) { cout << "That cell is taken." << endl; continue; }

        board[r][c] = markOf[player];
        moves++;

        if (checkWinner(markOf[player])) { printBoard(); cout << "Player " << player << " wins!" << endl; ended = true; break; }
        if (moves == 9) { printBoard(); cout << "It's a tie!" << endl; ended = true; break; }

        switchPlayer();
    }
}

//battle things
bool doAlchemist() {
    //at least 2 marks on the board
    int count = 0;
    for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) if (isOccupied(r,c)) count++;
    if (count < 2) { cout << "Not enough marks to swap yet." << endl; return false; }

    int a = askInt("Pick first cell to swap (1-9): ");
    int b = askInt("Pick second cell to swap (1-9): ");
    if (a < 1 || a > 9 || b < 1 || b > 9) { cout << "Cells must be 1..9." << endl; return false; }
    if (a == b) { cout << "Same cell twice does nothing." << endl; return false; }

    int r1,c1,r2,c2; cellToRC(a,r1,c1); cellToRC(b,r2,c2);
    if (!isOccupied(r1,c1) || !isOccupied(r2,c2)) { cout << "Both cells must contain marks." << endl; return false; }
    if (board[r1][c1] == board[r2][c2]) { cout << "Both cells have the same mark; swap is pointless." << endl; return false; }

    char tmp = board[r1][c1];
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = tmp;
    return true;
}

bool doPaladin() {
    //at least 1 mark somewhere
    int count = 0;
    for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) if (isOccupied(r,c)) count++;
    if (count < 1) { cout << "There are no marks to shift yet." << endl; return false; }

    int from = askInt("Pick a cell that has a mark to shift (1-9): ");
    int to   = askInt("Pick an adjacent empty cell (1-9): ");
    if (from < 1 || from > 9 || to < 1 || to > 9) { cout << "Cells must be 1..9." << endl; return false; }
    int r1,c1,r2,c2; cellToRC(from,r1,c1); cellToRC(to,r2,c2);
    if (!isOccupied(r1,c1)) { cout << "The FROM cell is empty." << endl; return false; }
    if (isOccupied(r2,c2))  { cout << "The TO cell is not empty." << endl; return false; }
    if (!isAdjacentCell(from, to)) { cout << "Destination must be adjacent (including diagonals)." << endl; return false; }

    board[r2][c2] = board[r1][c1];
    board[r1][c1] = char('1' + (r1*3 + c1)); 
    return true;
}

//battle mode
void playBattle() {
    resetBoard();
    int placements = 0; //only regular placements count toward 9

    while (!ended && placements < 9) {
        printBoard();
        cout << "Player " << player << " (" << markOf[player] << ") - Archetype: "
             << (archOf[player] == 1 ? "Paladin" : "Alchemist") << endl;

        cout << "Choose action:" << endl;
        cout << "  1) Regular move (place your mark)" << endl;
        if (archOf[player] == 2) {
            cout << "  2) Alchemist special (swap two marks)" << endl;
        } else {
            cout << "  2) Paladin special (shift one mark to an adjacent empty cell)" << endl;
        }

        int choice = askInt("Enter 1 or 2: ");
        if (choice != 1 && choice != 2) { cout << "Enter 1 or 2." << endl; continue; }

        bool usedSpecial = false;
        if (choice == 2) {
            if (archOf[player] == 2) usedSpecial = doAlchemist();
            else                     usedSpecial = doPaladin();
            if (!usedSpecial) { cout << "Special failed. Try again." << endl; continue; }
        } else {
            int cell = askInt("Enter a move (1-9): ");
            if (cell < 1 || cell > 9) { cout << "Choose 1..9." << endl; continue; }
            int r,c; cellToRC(cell,r,c);
            if (isOccupied(r,c)) { cout << "That cell is taken." << endl; continue; }
            board[r][c] = markOf[player];
            placements++;
        }

        if (checkWinner(markOf[player])) { printBoard(); cout << "Player " << player << " wins!" << endl; ended = true; break; }
        if (placements == 9) { printBoard(); cout << "It's a tie!" << endl; ended = true; break; }

        switchPlayer();
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << endl;

    bool again = true;
    while (again) {
        
        int mode = openingMenu();
        
        if (mode == 1) {
            setupRegular();
            playRegular();
        } else {
            setupBattle();
            playBattle();
        }

        again = playAgainMenu();
        if (again) {
            cout << endl;
            cout << "Starting a new game" << endl;
            cout << endl;
        } else {
            cout << "Bye!" << endl;
        }
    }

    return 0;
}