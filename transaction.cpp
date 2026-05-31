#include "transaction.h"

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
