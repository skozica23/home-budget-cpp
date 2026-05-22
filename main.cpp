#include "budget.h"

#include <iostream>
#include <limits>

int main() {
    Budget budget;
    int choice;

    do {
        std::cout << "\n----- HOME BUDGET -----"
                  << "\n1. Add"
                  << "\n2. Balance"
                  << "\n3. All"
                  << "\n4. Save"
                  << "\n5. Load"
                  << "\n0. Exit"
                  << "\n\nChoice: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                budget.add();
                break;
            case 2:
                budget.showBalance();
                break;
            case 3:
                budget.showAll();
                break;
            case 4:
                budget.save();
                break;
            case 5:
                budget.load();
                break;
            case 0:
                break;
            default:
                std::cout << "Please choose a number from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}