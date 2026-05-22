#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <fstream>

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

    void save(std::ofstream &file) const;

    static Transaction fromLine(const std::string &line);
};

#endif