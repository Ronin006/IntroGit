#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "Welcome to the Business Sorting Program!\n\n";

    std::vector<std::string> businesses;
    std::string name;
    std::string again;

    while (true) {
        std::cout << "Please enter the name of a business:  ";
        std::getline(std::cin, name);

        businesses.push_back(name);
        std::sort(businesses.begin(), businesses.end());

        if (businesses.size() == 1) {
            std::cout << "\nYour business is:\n\n";
        } else {
            std::cout << "\nYour businesses are:\n\n";
        }

        for (const auto& b : businesses) {
            std::cout << "    " << b << "\n";
        }

        std::cout << "\nAnother business?  ";
        std::getline(std::cin, again);

        if (!(again == "y" || again == "Y" || again == "yes" || again == "Yes")) {
            break;
        }

        std::cout << "\n";
    }

    std::cout << "\nThank you for using the Business Sorting Program!\n";
    return 0;
}
