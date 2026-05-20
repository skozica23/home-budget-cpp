# Home Budget - C++ CLI Application

A simple command-line application for managing home finances, developed to learn and practice the fundamentals of Object-Oriented Programming (OOP) in C++.

## 🚀 Features
* **Add Transactions:** Log incomes and expenses with categories, amounts, and custom descriptions.
* **Balance Calculation:** Automatically calculates the current balance with dynamic terminal color coding (Green for positive, Red for negative).
* **Formatted History:** Displays all transactions in a clean, well-aligned table using `<iomanip>`.
* **Data Persistence:** Save and load transaction history to/from a text file using a semicolon-separated format.

## 🛠️ Concepts Learned & Applied
* **Object-Oriented Programming:** Classes, encapsulation, constructors, and accessors (getters).
* **File I/O:** Reading and writing data using `std::ifstream` and `std::ofstream`.
* **STL Containers:** Managing dynamic data sequences with `std::vector`.
* **String Manipulation:** Parsing data rows via `std::string::find` and `std::string::substr`.

## 📈 Future Improvements (Roadmap)
* Refactor monolithic code into proper header (`.h`) and source (`.cpp`) files.
* Remove `using namespace std;` to avoid namespace pollution.
* Implement error handling (`try-catch` blocks) for safer file parsing (e.g., `std::stod` validation).