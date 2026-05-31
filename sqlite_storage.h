#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H

#include "transaction.h"
#include <vector>
#include <string>
#include <sqlite3.h>

class SQLiteStorage {
private:
    sqlite3* db;
    std::string db_Path;

public:
    explicit SQLiteStorage(const std::string& dbPath);
    ~SQLiteStorage();

    bool open();
    void close();
    bool initialize();

    bool saveTransactions(const std::vector<Transaction>& transactions);
    std::vector<Transaction> loadTransactions();
};

#endif