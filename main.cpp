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
                  << "\n6. Remove"
                  << "\n7. Summary"
                  << "\n8. Filter by Category"
                  << "\n9. Sort Transactions"
                  << "\n10. Update Transaction"
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
            case 6:
                budget.remove();
                break;
            case 7:
                budget.showSummary();
                break;
            case 8:
                budget.filterByCategory();
                break;
            case 9:
                budget.sortTransactions();
                break;
            case 10:
                budget.edit();
                break;
            case 0:
                break;
            default:
                std::cout << "Please choose a number from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}