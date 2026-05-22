#include "budget.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

void Budget::add() {
    std::string date;
    std::string category;
    std::string type;
    std::string description;
    double amount;

    std::cout << "Date: ";
    std::cin >> date;

    std::cout << "Category: ";
    std::cin >> category;

    std::cout << "Type (income/expense): ";
    std::cin >> type;

    std::cout << "Amount: ";
    std::cin >> amount;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Description: ";
    std::getline(std::cin, description);

    transactions.emplace_back(date, category, type, amount, description);

    std::cout << "Added!\n";
}

void Budget::showBalance() const {
    double balance = 0.0;

    for (const auto &transaction : transactions) {
        if (transaction.getType() == "income") {
            balance += transaction.getAmount();
        } else {
            balance -= transaction.getAmount();
        }
    }

    std::cout << (balance >= 0 ? "\033[32m" : "\033[31m");
    std::cout << "Balance: " << std::fixed << std::setprecision(2)
              << balance << " PLN\n";
    std::cout << "\033[0m";
}

void Budget::showAll() const {
    std::cout << std::left << std::setw(12) << "Date"
              << std::setw(15) << "Category"
              << std::setw(12) << "Type"
              << std::setw(10) << "Amount"
              << std::setw(25) << "Description"
              << "\n";

    std::cout << std::string(74, '-') << std::endl;

    for (const auto &transaction : transactions) {
        std::string color = transaction.getType() == "income" ? "\033[32m" : "\033[31m";

        std::cout << std::left << std::setw(12) << transaction.getDate()
                  << std::setw(15) << transaction.getCategory()
                  << color << std::setw(12) << transaction.getType() << "\033[0m"
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2)
                  << transaction.getAmount()
                  << "  "
                  << std::left << transaction.getDescription()
                  << std::endl;
    }
}

void Budget::save() const {
    std::ofstream file("budget.txt");

    if (!file) {
        std::cout << "Error: Could not open file for saving.\n";
        return;
    }

    for (const auto &transaction : transactions) {
        transaction.save(file);
    }

    std::cout << "Saved.\n";
}

void Budget::load() {
    std::ifstream file("budget.txt");

    if (!file) {
        std::cout << "Error: Could not open file for loading.\n";
        return;
    }

    transactions.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                transactions.push_back(Transaction::fromLine(line));
            } catch (const std::exception &error) {
                std::cout << "Skipped invalid line: " << line << "\n";
            }
        }
    }

    std::cout << "Loaded.\n";
}