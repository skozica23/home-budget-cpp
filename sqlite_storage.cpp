#include "sqlite_storage.h"
#include <iostream>

SQLiteStorage::SQLiteStorage(const std::string& dbPath)
: db(nullptr), db_Path(dbPath) {}

SQLiteStorage::~SQLiteStorage() {
    close();
}

bool SQLiteStorage::open() {
    if (sqlite3_open(db_Path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void SQLiteStorage::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool SQLiteStorage::initialize() {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "date TEXT NOT NULL,"
        "category TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "amount REAL NOT NULL,"
        "description TEXT"
        ");";

    char *errorMessage = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

bool SQLiteStorage::saveTransactions(const std::vector<Transaction> &transactions) {
    sqlite3_exec(db, "DELETE FROM transactions;", nullptr, nullptr, nullptr);

    const char *sql =
        "INSERT INTO transactions (date, category, type, amount, description) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    for (const auto &transaction : transactions) {
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cout << "Error preparing insert.\n";
            return false;
        }

        sqlite3_bind_text(stmt, 1, transaction.getDate().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, transaction.getCategory().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, transaction.getType().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 4, transaction.getAmount());
        sqlite3_bind_text(stmt, 5, transaction.getDescription().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cout << "Error inserting transaction.\n";
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    }

    return true;
}

std::vector<Transaction> SQLiteStorage::loadTransactions() {
    std::vector<Transaction> transactions;

    const char *sql =
        "SELECT date, category, type, amount, description "
        "FROM transactions "
        "ORDER BY id;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Error preparing select.\n";
        return transactions;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string category = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        double amount = sqlite3_column_double(stmt, 3);

        const unsigned char *descriptionText = sqlite3_column_text(stmt, 4);
        std::string description = descriptionText
            ? reinterpret_cast<const char *>(descriptionText)
            : "";

        transactions.emplace_back(date, category, type, amount, description);
    }

    sqlite3_finalize(stmt);

    return transactions;
}