# Home Budget App

A simple C++ console application for tracking personal income and expenses.

The project was created to practice basic C++ programming concepts, including classes, objects, vectors, user input, SQLite storage, and simple data persistence.

## Features

- Add income and expense transactions
- Store transaction data with date, category, type, amount, and description
- Display all saved transactions in a formatted table
- Calculate and display the current balance
- Save transactions to a local SQLite database
- Load transactions from a local SQLite database
- Display sample transactions from `sample-budget.db`
- Use basic terminal colors to distinguish income and expenses

## Project Structure

The code is planned to be organized into separate header and source files:

```text
HomeBudget/
├── main.cpp
├── transaction.h
├── transaction.cpp
├── budget.h
├── budget.cpp
├── sqlite_storage.h
└── sqlite_storage.cpp
```

## File Responsibilities

```text
main.cpp
```

Contains the main menu and controls the flow of the program.

```
transaction.h
```

Declares the `Transaction` class. A header file describes what the class looks like and what functions are available.

```
transaction.cpp
```

Defines how the `Transaction` class functions actually work.

```
budget.h
```

Declares the `Budget` class, which stores and manages multiple transactions.

```
budget.cpp
```

Defines the logic for adding transactions, showing the balance, displaying all transactions, saving data, and loading data.

```
sqlite_storage.h
```

Declares the `SQLiteStorage` class, which handles database access.

```
sqlite_storage.cpp
```

Creates the SQLite table and saves or loads transactions from `budget.db`.

## How To Build

Using CMake:

```bash
cmake -S . -B build
cmake --build build
```

The executable will be created in the `build` directory.

You can also compile manually with `g++` if SQLite is available on your system:

```bash
g++ main.cpp budget.cpp transaction.cpp sqlite_storage.cpp -lsqlite3 -o main
```

## How To Run

After building with CMake:

```
./build/home_budget
```

After compiling manually with `g++`:

```
./main
```

## Data Storage

The application saves and loads user data from a local SQLite database:

```
budget.db
```

This file is created automatically when the app saves or loads data. It should not be committed because it may contain private personal finance data.

The current implementation keeps transactions in memory while the app is running. Choosing `Save` writes the current list to SQLite, and choosing `Load` reads transactions back from SQLite.

The repository also includes `sample-budget.db` with test data. In the app, choose:

```
11. Show Sample Data
```

This displays the sample transactions without changing your current `budget.db`.

The database contains one table:

```sql
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    category TEXT NOT NULL,
    type TEXT NOT NULL,
    amount REAL NOT NULL,
    description TEXT
);
```

## What I Practiced

- Creating and using classes
- Constructor initialization lists
- Getters and encapsulation
- `std::vector`
- Reading user input with `std::cin` and `std::getline`
- Basic SQLite usage in C++
- Separating persistence logic into a storage class
- Formatting output with `std::setw`, `std::fixed`, and `std::setprecision`
- Splitting code into `.h` and `.cpp` files
- Avoiding `using namespace std;` in larger projects
- Basic error handling while loading data from a file

## Future Improvements Roadmap

- [x] Refactor monolithic code into proper header (`.h`) and source (`.cpp`) files
- [x] Remove `using namespace std;` to avoid namespace pollution
- [x] Implement basic error handling for safer file parsing, including `std::stod` validation
- [x] Add input validation when adding a new transaction
- [x] Add option to delete a transaction
- [x] Add option to search or filter transactions by category
- [x] Add income and expense summaries
- [x] Prevent semicolons in transaction fields
- [x] Add transactions sorting
- [x] Add transactions editing
- [x] Add CMake build configuration
- [x] Replace legacy file-based storage with SQLite
- [x] Move storage to SQLite
- [x] Remove legacy JSON storage from the application code
- [x] Add a sample SQLite database for testing

## Notes

This is a learning project. The goal is not only to build a working budget application, but also to show gradual progress in C++ code organization, readability, and safer data handling.
