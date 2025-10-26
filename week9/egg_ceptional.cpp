#include <iostream>
#include <string>
#include <exception>

using namespace std;

class bad_egg : public exception {
public:
    const char* what() const noexcept{
        return "You tried to eat a rotten egg!";
    }
};

class Egg {
protected:
    string size;
    string flavor;

public:
    Egg(string s, string f) : size(s), flavor(f) {}
    virtual ~Egg() {}

    string getSize() const { return size; }
    string getFlavor() const { return flavor; }

    virtual void eat_egg() const = 0;
};

class RegularEgg : public Egg {
public:
    RegularEgg(string s, string f) : Egg(s, f) {}
    void eat_egg() const {
        cout << "You eat a " << size << " egg with a " << flavor << " flavor." << endl;
    }
};

class SpicyEgg : public Egg {
public:
    SpicyEgg(string s, string f) : Egg(s, f) {}
    void eat_egg() const {
        cout << "You eat a " << size << " egg that tastes " << flavor << "." << endl;
    }
};

class RottenEgg : public Egg {
public:
    RottenEgg(string s) : Egg(s, "rotten") {}
    void eat_egg() const {
        throw bad_egg();
    }
};

class Carton {
private:
    Egg* eggs[12];
    int count;

public:
    Carton() { count = 0; }

    void add_egg(Egg* egg) {
        if (count < 12) {
            eggs[count] = egg;
            count++;
        } else {
            cout << "Carton is full!" << endl;
        }
    }

    void eat_next() {
        if (count == 0) {
            cout << "Carton is empty!" << endl;
            return;
        }

        count--;
        Egg* egg = eggs[count];

        try {
            egg->eat_egg();
        } catch (const bad_egg& e) {
            cout << "Warning: " << e.what() << endl;
        }

        delete egg;
    }
};

int main() {
    Carton carton;

    carton.add_egg(new RegularEgg("large", "buttery"));
    carton.add_egg(new SpicyEgg("medium", "peppery"));
    carton.add_egg(new RottenEgg("small"));

    cout << "--- Eating eggs ---" << endl;

    for (int i = 0; i < 3; i++) {
        carton.eat_next();
    }

    return 0;
}