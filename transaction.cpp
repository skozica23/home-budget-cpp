#include "transaction.h"

#include <vector>
#include <stdexcept>

Transaction::Transaction()
    : amount(0.0) {}

Transaction::Transaction(const std::string &d, const std::string &c, const std::string &t,
                         double am, const std::string &desc)
    : date(d), category(c), type(t), description(desc), amount(am) {}

std::string Transaction::getDate() const {
    return date;
}

std::string Transaction::getCategory() const {
    return category;
}

std::string Transaction::getType() const {
    return type;
}

std::string Transaction::getDescription() const {
    return description;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::save(std::ofstream &file) const {
    file << date << ";"
         << category << ";"
         << type << ";"
         << amount << ";"
         << description << "\n";
}

Transaction Transaction::fromLine(const std::string &line) {
    std::vector<std::string> data;
    size_t start = 0;
    size_t pos;

    while ((pos = line.find(';', start)) != std::string::npos) {
        data.push_back(line.substr(start, pos - start));
        start = pos + 1;
    }

    data.push_back(line.substr(start));

    if (data.size() != 5) {
        throw std::runtime_error("Invalid transaction line format.");
    }

    return Transaction(
        data[0],
        data[1],
        data[2],
        std::stod(data[3]),
        data[4]
    );
}

void Transaction::setDate(const std::string &newDate) {
    date = newDate;
}

void Transaction::setCategory(const std::string &newCategory) {
    category = newCategory;
}

void Transaction::setType(const std::string &newType) {
    type = newType;
}

void Transaction::setDescription(const std::string &newDescription) {
    description = newDescription;
}

void Transaction::setAmount(double newAmount) {
    amount = newAmount;
}