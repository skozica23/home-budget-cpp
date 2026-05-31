#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string date;
    std::string category;
    std::string type;
    std::string description;
    double amount;

public:
    Transaction();

    Transaction(const std::string &d, const std::string &c, const std::string &t,
                double am, const std::string &desc);

    std::string getDate() const;
    std::string getCategory() const;
    std::string getType() const;
    std::string getDescription() const;
    double getAmount() const;

    void setDate(const std::string &newDate);
    void setCategory(const std::string &newCategory);
    void setType(const std::string &newType);
    void setDescription(const std::string &newDescription);
    void setAmount(double newAmount);
};

#endif
