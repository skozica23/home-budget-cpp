#include "budget.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <algorithm>
#include <nlohmann/json.hpp>

// Converts a string to lowercase for case-insensitive comparisons
static std::string toLowerCase(std::string text) {
    for (char &character : text) {
        character = std::tolower(static_cast<unsigned char>(character));
    }

    return text;
}

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

   // CATEGORY VALIDATION
do {
    std::cout << "Category: ";
    std::cin >> category;

    if (category.empty()) {
        std::cout << "Category cannot be empty.\n";
    } else if (category.find(';') != std::string::npos) {
        std::cout << "Category cannot contain semicolons.\n";
        category.clear();
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
    std::ofstream file("budget.json");

    if (!file) {
        std::cout << "Error: Could not open file for saving.\n";
        return;
    }

    nlohmann::json transactionsJson = nlohmann::json::array();

    for (const auto &transaction : transactions) {
        transactionsJson.push_back(transaction.toJson());
    }

    file << transactionsJson.dump(4);

    std::cout << "Saved.\n";
}

void Budget::load() {
    std::ifstream file("budget.json");

    if (!file) {
        std::cout << "Error: Could not open file for loading.\n";
        return;
    }

    try {
        nlohmann::json transactionsJson;
        file >> transactionsJson;

        if (!transactionsJson.is_array()) {
            std::cout << "Error: Invalid JSON format. Expected an array.\n";
            return;
        }

        transactions.clear();

        for (const auto &item : transactionsJson) {
            try {
                transactions.push_back(Transaction::fromJson(item));
            } catch (const std::exception &error) {
                std::cout << "Skipped invalid transaction: " << error.what() << "\n";
            }
        }

        std::cout << "Loaded.\n";
    } catch (const std::exception &error) {
        std::cout << "Error: Could not parse JSON file: " << error.what() << "\n";
    }
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

        if (std::cin.fail() || index < 1 || index > transactions.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid index. Please try again.\n";
        }
    } while (std::cin.fail() || index >= transactions.size());

    transactions.erase(transactions.begin() + index - 1);
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

void Budget::filterByCategory() const {
    if (transactions.empty()) {
        std::cout << "No transactions to filter.\n";
        return;
    }

    std::string category;
    bool found = false;

    std::cout << "Enter category: ";
    std::cin >> category;
    
    std::string searchedCategory = toLowerCase(category);

    std::cout << std::left << std::setw(5) << "No."
              << std::setw(12) << "Date"
              << std::setw(15) << "Category"
              << std::setw(12) << "Type"
              << std::setw(10) << "Amount"
              << std::setw(25) << "Description"
              << "\n";

    std::cout << std::string(79, '-') << std::endl;

    for (size_t i = 0; i < transactions.size(); i++) {
        const auto &transaction = transactions[i];

        if (toLowerCase(transaction.getCategory()) == searchedCategory) {            std::string color = transaction.getType() == "income" ? "\033[32m" : "\033[31m";

            std::cout << std::left << std::setw(5) << i + 1
                      << std::setw(12) << transaction.getDate()
                      << std::setw(15) << transaction.getCategory()
                      << color << std::setw(12) << transaction.getType() << "\033[0m"
                      << std::right << std::setw(10) << std::fixed << std::setprecision(2)
                      << transaction.getAmount()
                      << "  "
                      << std::left << transaction.getDescription()
                      << std::endl;

            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found in this category.\n";
    }
}

void Budget::sortTransactions() {
    if (transactions.empty()) {
        std::cout << "No transactions to sort.\n";
        return;
    }

    int choice;

    std::cout << "\n----- SORT TRANSACTIONS -----"
              << "\n1. Sort by date"
              << "\n2. Sort by amount"
              << "\n0. Back"
              << "\n\nChoice: ";

    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number.\n";
        return;
    }

    switch (choice) {
        case 1:
            std::sort(transactions.begin(), transactions.end(),
                      [](const Transaction &a, const Transaction &b) {
                          return a.getDate() < b.getDate();
                      });
            std::cout << "Transactions sorted by date.\n";
            break;

        case 2:
            std::sort(transactions.begin(), transactions.end(),
                      [](const Transaction &a, const Transaction &b) {
                          return a.getAmount() < b.getAmount();
                      });
            std::cout << "Transactions sorted by amount.\n";
            break;

        case 0:
            break;

        default:
            std::cout << "Please choose a number from the menu.\n";
    }
}

void Budget::edit() {
    if (transactions.empty()) {
        std::cout << "No transactions to edit.\n";
        return;
    }

    showAll();

    size_t index;

    std::cout << "Enter the index of the transaction to edit: ";
    std::cin >> index;

    if (std::cin.fail() || index < 1 || index > transactions.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid index. Please try again.\n";
        return;
    }

    Transaction &transaction = transactions[index - 1];

    std::string date;
    std::string category;
    std::string type;
    std::string description;
    double amount;

    do {
        std::cout << "New date (YYYY-MM-DD): ";
        std::cin >> date;

        if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
            date.clear();
        }
    } while (date.empty());

    do {
        std::cout << "New category: ";
        std::cin >> category;

        if (category.empty()) {
            std::cout << "Category cannot be empty.\n";
        } else if (category.find(';') != std::string::npos) {
            std::cout << "Category cannot contain semicolons.\n";
            category.clear();
        }
    } while (category.empty());

    do {
        std::cout << "New type (income/expense): ";
        std::cin >> type;

        if (type != "income" && type != "expense") {
            std::cout << "Invalid type. Please enter 'income' or 'expense'.\n";
        }
    } while (type != "income" && type != "expense");

    do {
        std::cout << "New amount: ";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid amount. Please enter a number greater than 0.\n";
            amount = 0;
        }
    } while (amount <= 0);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        std::cout << "New description: ";
        std::getline(std::cin, description);

        if (description.find(';') != std::string::npos) {
            std::cout << "Description cannot contain semicolons.\n";
        }
    } while (description.find(';') != std::string::npos);

    transaction.setDate(date);
    transaction.setCategory(category);
    transaction.setType(type);
    transaction.setAmount(amount);
    transaction.setDescription(description);

    std::cout << "Transaction updated.\n";
}
