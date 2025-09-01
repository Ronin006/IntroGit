#include <cassert>
#include <string>
#include <random>

class Student {
public:
    std::string first_name;
    std::string last_name;

    Student(std::string fn, std::string ln)
        : first_name(fn), last_name(ln), number_of_credits(0) 
    {
        // Generate random student ID
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(10000, 99999);
        student_id = dist(gen);
    }

    // read-only access to student_id
    int get_student_id() const {
        return student_id;
    }

    // read-only access to credits
    int get_number_of_credits() const {
        return number_of_credits;
    }

    void add_credits(int number) {
        number_of_credits += number;
    }

    void reset_credits() {
        number_of_credits = 0;
    }

    // ⚠️ Public for asserts in your test — but better practice would be private + getters
    int number_of_credits;

private:
    int student_id;
};

int main() {
    Student student = Student("Bob", "Bobberson");

    assert(student.first_name == "Bob");
    assert(student.number_of_credits == 0);

    student.add_credits(6);
    student.add_credits(2);

    assert(student.number_of_credits == 8);

    student.reset_credits();

    assert(student.number_of_credits == 0);

    return 0;
}
