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

    //DATE VALIDATION
    do {
        std::cout << "Date (YYYY-MM-DD): ";
        std::cin >> date;
        if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
            date.clear();
        }
    } while (date.empty());

    //CATEGORY VALIDATION
    do {
        std::cout << "Category: ";
        std::cin >> category;
        if (category.empty()) {
            std::cout << "Category cannot be empty.\n";
        }
    } while (category.empty());

    //TYPE VALIDATION
    do {
        std::cout << "Type (income/expense): ";
        std::cin >> type;

        if (type != "income" && type != "expense") {
            std::cout << "Invalid type. Please enter 'income' or 'expense'.\n";
        }
    } while (type != "income" && type != "expense");

    //AMOUNT VALIDATION
   do {
        std::cout << "Amount: ";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid amount. Please enter a number greater than 0.\n";
            amount = 0;
        }
    } while (amount <= 0);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //DESCRIPTION VALIDATION
    do {
        std::cout << "Description: ";
        std::getline(std::cin, description);

        if (description.find(';') != std::string::npos) {
            std::cout << "Description cannot contain semicolons.\n";
        }
    } while (description.find(';') != std::string::npos);

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
    std::cout << std::left << std::setw(5) << "Index" << std::setw(12) << "Date"
              << std::setw(15) << "Category"
              << std::setw(12) << "Type"
              << std::setw(10) << "Amount"
              << std::setw(25) << "Description"
              << "\n";

    std::cout << std::string(74, '-') << std::endl;

    for (size_t i = 0; i < transactions.size(); i++) {
    const auto &transaction = transactions[i];

    std::string color = transaction.getType() == "income" ? "\033[32m" : "\033[31m";

    std::cout << std::left << std::setw(5) << i + 1
              << std::setw(12) << transaction.getDate()
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

void Budget::remove() {
    if (transactions.empty()) {
        std::cout << "No transactions to remove.\n";
        return;
    }

    size_t index;
    do {
        std::cout << "Enter the index of the transaction to remove: ";
        std::cin >> index;

        if (std::cin.fail() || index >= transactions.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid index. Please try again.\n";
        }
    } while (std::cin.fail() || index >= transactions.size());

    transactions.erase(transactions.begin() + index);
    std::cout << "Transaction removed.\n";
}

void Budget::showSummary() const {
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    for (const auto &transaction : transactions) {
        if (transaction.getType() == "income") {
            totalIncome += transaction.getAmount();
        } else if (transaction.getType() == "expense") {
            totalExpenses += transaction.getAmount();
        }
    }

    double balance = totalIncome - totalExpenses;

    std::cout << "\n----- SUMMARY -----\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total income:   " << totalIncome << " PLN\n";
    std::cout << "Total expenses: " << totalExpenses << " PLN\n";

    std::cout << (balance >= 0 ? "\033[32m" : "\033[31m");
    std::cout << "Balance:        " << balance << " PLN\n";
    std::cout << "\033[0m";
}