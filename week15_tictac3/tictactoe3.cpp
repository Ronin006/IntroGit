#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

char board[3][3];
bool playerTurn = true;
char markOf[3] = {'?', 'X', 'O'}; // Player = X, Foe = O

bool specialUsedThisMatch = false; // allow it once per match
bool foeMimicUsedThisMatch = false; // mimic copies class special 

// you should play Elden Ring if u haven't played it already, great story and challenging gameplay

// -------------------------- INPUT HELPERS --------------------------
int askInt(const string& msg) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Wrong input. Try again." << endl;
    }
}

string askWord(const string& msg) {
    cout << msg;
    string s;
    cin >> s;
    return s;
}

int askIntInRange(const string& msg, int lo, int hi) {
    while (true) {
        int x = askInt(msg);                
        if (x >= lo && x <= hi) return x;   
        cout << "Wrong input. Enter a number between " << lo << " and " << hi << "." << endl;
    }
}
// -------------------------- BOARD HELPERS --------------------------
void cellToRC(int cell, int &r, int &c) {
    r = (cell - 1) / 3;
    c = (cell - 1) % 3;
}
bool isOccupied(int r, int c) {
    return board[r][c] != char('1' + r * 3 + c);
}
void resetBoard() {
    int n = 1;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = char('0' + n++);
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
void opponentMove() {
    int empty[9], k = 0;
    for (int cell = 1; cell <= 9; cell++) {
        int r, c;
        cellToRC(cell, r, c);
        if (!isOccupied(r, c)) empty[k++] = cell;
    }
    if (k == 0) return;
    int pick = empty[rand() % k];
    int r, c;
    cellToRC(pick, r, c);
    board[r][c] = 'O';
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
// -------------------------- GAME DATA --------------------------

enum FoeSpecial {
    NONE,
    EXTRA_MOVE,
    HEAL_SELF,
    SHIELD,
    DESTROY_MARK
};

struct Player {
    string name;
    int cls; // 1 Paladin, 2 Alchemist
    int maxHP, curHP, dmg, def;
    int runes; // currency
    int estusMax, estusCur; // healing
    int actIndex; // location of player
    bool helpedRanni; // plot turn
    bool gotFingerslayer; // plot turn
};

struct Foe {
    string name;
    int maxHP, curHP, dmg, def;
    int runesReward; 
    FoeSpecial special1;
    FoeSpecial special2; // used only for final boss
};

struct Location {
    string actName;
    string locationName;
    string prologueText; // story text for each act/location
    string nextWhyText; // story text
    Foe commonFoe;
    Foe boss;
    bool isOptional;
    bool requiresRanni; // smells fishy or not?
    bool marksQuestItem;
};



// -------------------------- SAVE/LOAD --------------------------
bool load(Player& p) {
    ifstream in("save.txt");
    if (!in) return false;

    getline(in, p.name);
    in >> p.cls >> p.maxHP >> p.curHP >> p.dmg >> p.def
       >> p.runes >> p.estusMax >> p.estusCur
       >> p.actIndex >> p.helpedRanni >> p.gotFingerslayer;

    return (bool)in;
}
void save(const Player& p) {
    ofstream out("save.txt", ios::trunc);
    out << p.name << endl;
    out << p.cls << " " << p.maxHP << " " << p.curHP << " " << p.dmg << " " << p.def << " "
        << p.runes << " " << p.estusMax << " " << p.estusCur << " "
        << p.actIndex << " " << p.helpedRanni << " " << p.gotFingerslayer << endl;
}
void resetSave() {
    ofstream out("save.txt", ios::trunc);
}

// -------------------------- ABILITIES --------------------------
bool doAlchemist() {
    //at least 2 marks on the board
    int count = 0;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (isOccupied(r,c)) count++;

    if (count < 2) { cout << "Not enough marks to swap yet." << endl; return false; }

    int a = askIntInRange("Pick first cell to swap (1-9): ", 1, 9);
    int b = askIntInRange("Pick second cell to swap (1-9): ", 1, 9);
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
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (isOccupied(r,c)) count++;

    if (count < 1) { cout << "There are no marks to shift yet." << endl; return false; }

    int from = askIntInRange("Pick a cell that has a mark to shift (1-9): ", 1, 9);
    int to   = askIntInRange("Pick an adjacent empty cell (1-9): ", 1, 9);
    if (from < 1 || from > 9 || to < 1 || to > 9) { cout << "Cells must be 1..9." << endl; return false; }

    int r1,c1,r2,c2; cellToRC(from,r1,c1); cellToRC(to,r2,c2);
    if (!isOccupied(r1,c1)) { cout << "The FROM cell is empty." << endl; return false; }
    if (isOccupied(r2,c2))  { cout << "The TO cell is not empty." << endl; return false; }
    if (!isAdjacentCell(from, to)) { cout << "Destination must be adjacent (including diagonals)." << endl; return false; }

    board[r2][c2] = board[r1][c1];
    board[r1][c1] = char('1' + (r1*3 + c1));
    return true;
}
void useFoeSpecial(Foe& f) {
    auto applySpecial = [&](FoeSpecial sp) {
        int roll = rand() % 100;

        if (sp == EXTRA_MOVE && roll < 25) {
            cout << f.name << " uses SPECIAL: Extra Move!\n";
            opponentMove();
        }
        else if (sp == HEAL_SELF && roll < 30) {
            cout << f.name << " uses SPECIAL: Regeneration!\n";
            f.curHP = min(f.maxHP, f.curHP + 8);
        }
        else if (sp == SHIELD && roll < 25) {
            cout << f.name << " uses SPECIAL: Harden!\n";
            f.def = min(f.def + 1, 12);; // for the rest of curr battle
        }
        else if (sp == DESTROY_MARK && roll < 20) {
            cout << f.name << " uses SPECIAL: Shatter Mark!\n";
            int idx = rand() % 9;
            int r = idx / 3, c = idx % 3;
            if (isOccupied(r, c)) {
                board[r][c] = char('1' + idx);
            } else {
                cout << "(But it hit an empty cell.)\n";
            }
        }
    };

    if (f.special1 != NONE) {
        applySpecial(f.special1);
    }

    // only when below 50% HP 
    if (f.special2 != NONE && f.curHP <= f.maxHP / 2) {
        int roll2 = rand() % 100;
        if (roll2 < 40) {                // phase-2 chance
            applySpecial(f.special2);
        }
    }
}
// if player paladin
bool mimicShiftAI() {
    int occ[9], occN = 0;
    for (int cell = 1; cell <= 9; cell++) {
        int r, c; cellToRC(cell, r, c);
        if (isOccupied(r, c)) occ[occN++] = cell;
    }
    if (occN == 0) return false;

    for (int tries = 0; tries < 30; tries++) {
        int from = occ[rand() % occN];
        int r1, c1; cellToRC(from, r1, c1);

        int dr = (rand() % 3) - 1;
        int dc = (rand() % 3) - 1;
        if (dr == 0 && dc == 0) continue;

        int r2 = r1 + dr;
        int c2 = c1 + dc;
        if (r2 < 0 || r2 > 2 || c2 < 0 || c2 > 2) continue;

        int to = (r2 * 3 + c2) + 1;
        if (!isAdjacentCell(from, to)) continue;
        if (isOccupied(r2, c2)) continue;

        board[r2][c2] = board[r1][c1];
        board[r1][c1] = char('1' + (r1 * 3 + c1));
        return true;
    }
    return false;
}

// if player alchemist
bool mimicSwapAI() {
    int occ[9], occN = 0;
    for (int cell = 1; cell <= 9; cell++) {
        int r, c; cellToRC(cell, r, c);
        if (isOccupied(r, c)) occ[occN++] = cell;
    }
    if (occN < 2) return false;

    for (int tries = 0; tries < 40; tries++) {
        int a = occ[rand() % occN];
        int b = occ[rand() % occN];
        if (a == b) continue;

        int r1, c1, r2, c2;
        cellToRC(a, r1, c1);
        cellToRC(b, r2, c2);

        if (board[r1][c1] == board[r2][c2]) continue;

        char tmp = board[r1][c1];
        board[r1][c1] = board[r2][c2];
        board[r2][c2] = tmp;
        return true;
    }
    return false;
}

// -------------------------- MATCH --------------------------

int playOneMatch(const Player& p, Foe& foe) {
    resetBoard();
    specialUsedThisMatch = false;
    foeMimicUsedThisMatch = false;
    int turns = 0;
    playerTurn = true;

    while (true) {
        if (playerTurn) {
            printBoard();
            cout << "Your turn (X)\n";
            cout << "1) Regular move\n";
            cout << "2) Special ability (once per match)\n";
            int choice = askIntInRange("Choose: ", 1, 2);

            if (choice == 2) {
                if (specialUsedThisMatch) {
                    cout << "Ability already used this match." << endl;
                    continue;
                }

                bool ok = false;
                if (p.cls == 1) ok = doPaladin();
                else if (p.cls == 2) ok = doAlchemist();
                else { cout << "No special for this class." << endl; ok = false; }

                if (ok) {
                    specialUsedThisMatch = true;
                    turns++;            // special consumes a turn
                    playerTurn = false; 
                }
                continue;
            }

            int cell = askIntInRange("Pick cell (1-9): ", 1, 9);
            int r, c;
            cellToRC(cell, r, c);
            if (cell < 1 || cell > 9 || isOccupied(r, c)) continue;
            board[r][c] = 'X';
            turns++;
        } else {
            bool didMimic = false;

            if (foe.name == "Mimic Tear" && !foeMimicUsedThisMatch) {
                int roll = rand() % 100;
                if (roll < 35) { 
                    cout << foe.name << " copies your technique!\n";
                    if (p.cls == 1) didMimic = mimicShiftAI(); 
                    else if (p.cls == 2) didMimic = mimicSwapAI(); 

                    if (didMimic) foeMimicUsedThisMatch = true;
                }
            }

            if (!didMimic) opponentMove(); // normal move if it didn't mimic

            useFoeSpecial(foe); // still can have its own special fix
            turns++;
        }

        if (checkWinner('X')) return 1;
        if (checkWinner('O')) return 2;
        if (turns >= 9) return 0;

        playerTurn = !playerTurn;
    }
}

// -------------------------- BATTLE --------------------------
int damage(int dmg, int def) { return max(0, dmg - def); }

bool doBattle(Player& p, Foe foe) {
    if (foe.name == "Mimic Tear") {
        foe.maxHP = p.maxHP;
        foe.dmg = p.dmg;
        foe.def = p.def;
    }
    foe.curHP = foe.maxHP;
    cout << endl << "BATTLE START: " << foe.name << endl;

    while (p.curHP > 0 && foe.curHP > 0) {
        cout << endl;
        cout << "You: " << p.curHP << "/" << p.maxHP
             << "  ATK " << p.dmg << "  DEF " << p.def
             << "  Estus " << p.estusCur << "/" << p.estusMax
             << "  Runes " << p.runes << endl;

        cout << foe.name << ": " << foe.curHP << "/" << foe.maxHP
             << "  ATK " << foe.dmg << "  DEF " << foe.def << endl;

        cout << "1) Fight (tic-tac-toe)" << endl;
        cout << "2) Use estus (+12 HP)" << endl;
        int c = askIntInRange("Choose: ", 1, 2);

        if (c == 2) {
            if (p.estusCur <= 0) cout << "No estus left." << endl;
            else {
                p.estusCur--;
                p.curHP = min(p.maxHP, p.curHP + 12);
                cout << "You drink estus." << endl;
            }
            continue;
        }

        int r = playOneMatch(p, foe);

        if (r == 1) {
            int d = damage(p.dmg, foe.def);
            foe.curHP = max(0, foe.curHP - d);
            cout << "You won the match. " << foe.name << " takes " << d << " damage." << endl;
        } else if (r == 2) {
            int d = damage(foe.dmg, p.def);
            p.curHP = max(0, p.curHP - d);
            cout << foe.name << " won the match. You take " << d << " damage." << endl;
        } else {
            cout << "Tie. No damage." << endl;
        }
    }

    if (p.curHP <= 0) return false;

    cout << endl << foe.name << " defeated. +" << foe.runesReward << " runes." << endl;
    p.runes += foe.runesReward;
    return true;
}

// -------------------------- BONFIRE --------------------------
void bonfire(Player& p) {
    while (true) {
        cout << endl << "<=== BONFIRE (SHOP) ===>" << endl;
        cout << "Runes: " << p.runes << endl;
        cout << "1) Upgrade ATK +1 (10 runes)" << endl;
        cout << "2) Upgrade DEF +1 (10 runes)" << endl;
        cout << "3) Upgrade Max HP +10 (12 runes)" << endl;
        cout << "4) Buy +1 Estus charge (15 runes) [max 8]" << endl;
        cout << "5) Return" << endl;

        int c = askIntInRange("Choose: ", 1, 5);
        if (c == 5) return;

        if (c == 1 && p.runes >= 10) { p.runes -= 10; p.dmg++; cout << "ATK upgraded." << endl; }
        else if (c == 2 && p.runes >= 10) { p.runes -= 10; p.def++; cout << "DEF upgraded." << endl; }
        else if (c == 3 && p.runes >= 12) {
            p.runes -= 12;
            p.maxHP += 10;
            p.curHP = min(p.maxHP, p.curHP + 10);
            cout << "Max HP upgraded." << endl;
        }
        else if (c == 4 && p.runes >= 15) {
            if (p.estusMax >= 8) cout << "Estus is already at cap." << endl;
            else { p.runes -= 15; p.estusMax++; cout << "Estus charge increased." << endl; }
        }
        else cout << "Not enough runes (or invalid choice)." << endl;
    }
}

void useEstusOutOfCombat(Player& p) {
    cout << endl << "=== ESTUS ===" << endl;
    if (p.estusCur <= 0) { cout << "No estus left." << endl; return; }
    if (p.curHP >= p.maxHP) { cout << "HP is already full." << endl; return; }
    p.estusCur--;
    p.curHP = min(p.maxHP, p.curHP + 12);
    cout << "You drink estus. HP restored." << endl;
}

void graceBetweenLocations(Player& p) {
    p.curHP = min(p.maxHP, p.curHP + 10);
    p.estusCur = min(p.estusMax, p.estusCur + 1);
    cout << endl << "Grace: +10 HP and +1 estus recharge." << endl;
}

// -------------------------- STORY: RANNI QUEST --------------------------
void offerRanniQuest(Player& p) {
    if (p.helpedRanni) return;
    cout << endl << "A pale witch appears: Ranni." << endl;
    cout << "She says the Golden Order controls fate, and she wants a new age under the stars." << endl;
    cout << "If you help her, you may change the ending." << endl;
    cout << "1) Help Ranni" << endl;
    cout << "2) Refuse" << endl;
    int c = askIntInRange("Choose: ",1 ,2);
    if (c == 1) { p.helpedRanni = true; cout << "Ranni: Seek the Fingerslayer Blade in Nokron. Bring it to me." << endl; }
    else { p.helpedRanni = false; cout << "You refuse. The throne path continues." << endl; }
}

// -------------------------- MENU --------------------------
int openingMenu() {
    cout << "Welcome to Tic Tac Toe Elden Ring Game" << endl;
    cout << "1) New Game" << endl;
    cout << "2) Load Save" << endl;
    while (true) {
        return askIntInRange("Choose: ", 1, 2);
    }
}

void explainClasses() {
    cout << endl;
    cout << " CLASSES " << endl;
    cout << "Paladin:" << endl;
    cout << "- Higher HP and DEF, safer, slower kills." << endl;
    cout << "- Special (once per match): SHIFT" << endl;
    cout << "  Move any mark (X or O) into an adjacent empty cell." << endl;
    cout << endl;
    cout << "Alchemist:" << endl;
    cout << "- Higher ATK, lower HP/DEF, faster kills but riskier." << endl;
    cout << "- Special (once per match): SWAP" << endl;
    cout << "  Swap two different marks already on the board." << endl;
    cout << endl;
    cout << "Combat rule:" << endl;
    cout << "- If you win a tic-tac-toe match: foe loses (your ATK - foe DEF) HP" << endl;
    cout << "- If foe wins: you lose (foe ATK - your DEF) HP" << endl;
    cout << "- Ties do no damage" << endl;
    cout << "- Damage never goes below 0" << endl;
    cout << endl;
    cout << "Player is X, Foe is O" << endl;
    cout << endl;
}

void newGame(Player& p) {
    p.name = askWord("Choose your character's name: ");
    explainClasses();

    p.cls = askIntInRange("Choose class (1 Paladin, 2 Alchemist): ", 1, 2);

    if (p.cls == 1) { p.maxHP = p.curHP = 45; p.dmg = 8;  p.def = 4; }
    else            { p.maxHP = p.curHP = 38; p.dmg = 10; p.def = 2; }

    p.runes = 10;
    p.estusMax = 3;
    p.estusCur = 3;
    p.actIndex = 0;
    p.helpedRanni = false;
    p.gotFingerslayer = false;
}

bool locationAccessible(const Player& p, const Location& L) {
    if (!L.isOptional) return true;
    if (L.requiresRanni && !p.helpedRanni) return false;
    if (L.marksQuestItem && p.gotFingerslayer) return false;
    return true;
}

bool afterLocationMenu(Player& p, bool canOfferRanni) {
    while (true) {
        cout << endl << "<=== CHOICE ===>" << endl;
        cout << "1) Use bonfire (shop)" << endl;
        cout << "2) Use estus (+HP)" << endl;
        cout << "3) Save progress" << endl;
        cout << "4) Move on" << endl;
        if (canOfferRanni && !p.helpedRanni) cout << "5) Optional quest: Speak to Ranni" << endl;

        int maxChoice = (canOfferRanni && !p.helpedRanni) ? 5 : 4; // fixed?
        int c = askIntInRange("Choose: ", 1, maxChoice);
        if (c == 1) bonfire(p);
        else if (c == 2) useEstusOutOfCombat(p);
        else if (c == 3) { save(p); cout << "Saved." << endl; }
        else if (c == 4) return true;
        else if (c == 5 && canOfferRanni && !p.helpedRanni) offerRanniQuest(p);
        else cout << "Invalid choice." << endl;
    }
}

int endingMenu() {
    cout << endl << "1) Start a new game" << endl;
    cout << "2) Exit" << endl;
    while (true) {
        int c = askIntInRange("Choose: ",1 ,2);
        if (c == 1 || c == 2) return c;
    }
}

int main() {
    srand((unsigned)time(nullptr));

    Location acts[] = { //maxHP, curHP, dmg, def, runes award
        {
            "ACT 1", "Limgrave",
            "Prologue – Limgrave\n\n"
            "Long ago, you were Tarnished.\n\n"
            "The Tarnished are warriors once blessed by Grace, stripped of it, and exiled from the Lands Between.\n"
            "Without Grace, they lost purpose, power, and the right to rule.\n"
            "Now, Grace has returned — faint, flickering — calling the Tarnished back to compete for the Elden Ring.\n\n"
            "The world is governed by the Golden Order, interpreted by the Two Fingers.\n"
            "The Fingers claim to speak the will of a higher power, guiding who may rule and how the world must exist.\n\n"
            "You awaken in Limgrave, weak but chosen.\n"
            "If you follow Grace, you may restore the Order and become Elden Lord.\n"
            "If you defy it, you may uncover truths the Fingers wish buried.\n\n"
            "Your path begins here.\n",
            "Next: Stormveil. A Great Rune waits. Power is needed to face the capital.",
            {"Gatefront Soldier", 25,25, 10,4, 25, NONE, NONE},
            {"Godrick the Grafted", 40,40, 13,6, 40, EXTRA_MOVE, NONE},
            false, false, false
        },
        {
            "ACT 2", "Liurnia of the Lakes",
            "Liurnia: fog, ruins, and sorcery. Knowledge can be another kind of power.",
            "Next: Leyndell. The capital blocks the throne. You need strength to enter.",
            {"Raya Lucaria Scholar", 28,28, 12,5, 30, NONE, NONE},
            {"Rennala, Queen of the Full Moon", 45,45, 14,6, 45, HEAL_SELF, NONE},
            false, false, false
        },
        {
            "ACT 2.5 (OPTIONAL)", "Nokron, Eternal City",
            "Nokron: hidden below. Ranni's request leads you here for a forbidden blade.",
            "Next: Leyndell. The main path returns to the capital.",
            {"Silver Tear", 30,30, 13,6, 35, NONE, NONE},
            {"Mimic Tear", 1,1, 1,1, 50, NONE, NONE}, // has players ability and stats
            true, true, true
        },
        {
            "ACT 3", "Leyndell, Royal Capital",
            "Leyndell: the city of gold. The path to the Elden Ring is guarded by a king.",
            "Next: Farum Azula. A storm beyond time, where fate is cut loose.",
            {"Leyndell Knight", 32,32, 14,7, 45, NONE, NONE},
            {"Morgott, the Omen King", 50,50, 17,8, 50, SHIELD, NONE},
            false, false, false
        },
        {
            "ACT 4", "Crumbling Farum Azula",
            "Farum Azula: crumbling stones and howling winds. The blade of death awaits.",
            "Next: The final battle. Decide the world you will create.",
            {"Beastman of Farum Azula", 36,36, 16,8, 55, NONE, NONE},
            {"Maliketh, the Black Blade", 55,55, 19,9, 100, DESTROY_MARK, NONE},
            false, false, false
        },
        {
            "ACT 5", "Ashen Capital",
            "Ashen Capital: everything burns. Only the Elden Ring remains.",
            "End: Choose your ending.",
            {"Erdtree Remnant", 40,40, 17,9, 70, NONE, NONE},
            {"Radagon / Elden Beast", 75,75, 20,10, 0, SHIELD, DESTROY_MARK},
            false, false, false
        }
    };

    const int actCount = (int)(sizeof(acts) / sizeof(acts[0]));

    while (true) {
        Player p;

        int menu = openingMenu();
        if (menu == 2) {
            if (!load(p)) {
                cout << "No save found. Starting new game." << endl;
                newGame(p);
                save(p);
            } else {
                cout << "Save loaded." << endl;
            }
        } else {
            newGame(p);
            save(p);
        }

        cout << endl << "<==== STORY START ====>" << endl;
        cout << acts[0].prologueText << endl;

        int i = p.actIndex;
        while (i < actCount) {
            if (acts[i].isOptional && !locationAccessible(p, acts[i])) {
                i++;
                p.actIndex = i;
                save(p);
                continue;
            }

            cout << endl << "-----------------------------------" << endl;
            cout << acts[i].actName << ": " << acts[i].locationName << endl;
            cout << acts[i].prologueText << endl;

            cout << endl << "Location battle 1: Common foe -> " << acts[i].commonFoe.name << endl;
            if (!doBattle(p, acts[i].commonFoe)) {
                cout << endl << "YOU DIED." << endl;
                resetSave();
                break;
            }

            cout << endl << "Location battle 2: Final boss -> " << acts[i].boss.name << endl;
            if (!doBattle(p, acts[i].boss)) {
                cout << endl << "YOU DIED." << endl;
                resetSave();
                break;
            }

            if (acts[i].marksQuestItem) {
                p.gotFingerslayer = true;
                cout << endl << "You obtained: Fingerslayer Blade." << endl;
                cout << "This can change something if you promised to help Ranni." << endl;
            }

            graceBetweenLocations(p);

            cout << endl << "Next location info:" << endl;
            cout << acts[i].nextWhyText << endl;

            bool canOfferRanni = (acts[i].locationName == "Liurnia of the Lakes");
            bool moveOn = afterLocationMenu(p, canOfferRanni);
            if (!moveOn) continue;

            i++;
            p.actIndex = i;
            save(p);
        }

        if (p.curHP <= 0) {
            int endC = endingMenu();
            if (endC == 1) { resetSave(); continue; }
            return 0;
        }

        if (p.actIndex >= actCount) {
            cout << endl << "-----------------------------------" << endl;
            cout << "ENDING SUMMARY" << endl;
            cout << "Helped Ranni: " << (p.helpedRanni ? "YES" : "NO") << endl;
            cout << "Fingerslayer Blade: " << (p.gotFingerslayer ? "YES" : "NO") << endl;

            cout << endl << "-----------------------------------" << endl;
            if (p.helpedRanni && p.gotFingerslayer) {
                cout << "ENDING: Age of Stars" << endl;
                cout << "You chose a world guided by cold starlight and distant fate." << endl;
            } else {
                cout << "ENDING: Elden Lord" << endl;
                cout << "You claimed the throne and continued the Order under your rule." << endl;
            }
            cout << "-----------------------------------" << endl;

            int endC = endingMenu();
            if (endC == 1) { resetSave(); continue; }
            return 0;
        }
    }
}