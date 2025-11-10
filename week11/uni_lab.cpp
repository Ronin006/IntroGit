#include <iostream>
#include <string>
#include <set>
#include <memory>
#include <stdexcept>

using namespace std;

class Unicorn {
private:
    string name;
    static set<string> taken;   

public:
    //throws if name already taken
    Unicorn(const string& n) {
        if (taken.count(n)) {
            throw runtime_error("Name already taken: " + n);
        }
        name = n;
        taken.insert(name);
        cout << "created unicorn: " << name << endl;
    }

    ~Unicorn() {
        cout << "destroyed unicorn: " << name << endl;
        taken.erase(name);
    }

    void print() const {
        cout << "unicorn: " << name << endl;
    }

    //helper to show currently taken names
    static void show_taken() {
        cout << "taken names: ";
        for (auto it = taken.begin(); it != taken.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

//static storage definition
set<string> Unicorn::taken;

int main() {
    try {
        //smart pointers manage lifetime automatically
        unique_ptr<Unicorn> u1 = make_unique<Unicorn>("Astra");
        unique_ptr<Unicorn> u2 = make_unique<Unicorn>("Blaze");

        Unicorn::show_taken();

        //duplicate name -> throws
        try {
            unique_ptr<Unicorn> bad = make_unique<Unicorn>("Astra");
        } catch (const exception& e) {
            cout << "caught: " << e.what() << endl;
        }

        //free a name by destroying the object, then reuse it
        cout << "resetting u1 (Astra)..." << endl;
        u1.reset();  //destructor runs, "Astra" becomes available

        Unicorn::show_taken();

        //reuse the freed name successfully
        unique_ptr<Unicorn> u3 = make_unique<Unicorn>("Astra");
        u3->print();

        Unicorn::show_taken();
    }
    catch (const exception& e) {
        cout << "error: " << e.what() << endl;
    }

    cout << "done" << endl;
    return 0;
}