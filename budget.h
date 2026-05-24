#ifndef BUDGET_H
#define BUDGET_H

#include "transaction.h"

#include <vector>

class Budget {
private:
    std::vector<Transaction> transactions;

public:
    void add();
    void showBalance() const;
    void showAll() const;
    void save() const;
    void load();
    void remove();
    void showSummary() const;
};

#endif