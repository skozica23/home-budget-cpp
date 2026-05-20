#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
//--------------------------------------------------------------
//                      TRANSACTION CLASS
//--------------------------------------------------------------

class Transaction {

    string date;
    string category;
    string type;       
    string description;
    double amount;

public:

    // Empty constructor
    // default constructor, creates an empty object
    // needed for reading from a file
    Transaction() {}

    // Parameterized constructor - creates the object immediately
    Transaction(const string &d, const string &c, const string &t,
               double am, const string &desc)
        : date(d), category(c), type(t), amount(am), description(desc) {}
        // constructor initialization list, creates the object directly

    // getters allow the Budget class to read data from the transaction
    // const meaning constant, protects against accidental modification
    // return returns the value
    string getDate() const { return date; }
    string getCategory() const { return category; }
    string getType() const { return type; }
    string getDescription() const { return description; }
    double getAmount() const { return amount; }

    // Save to a file in CSV format
    void save(ofstream &file) const {
        file << date << ";" 
             << category << ";" 
             << type << ";" 
             << amount << ";" 
             << description << "\n"; // after adding the description - a new line
    }

    // Creating an object from a single CSV line
    static Transaction fromLine(const string &line) { // static method – called without an object
        vector<string> data;    // vector of fragments cut from the line
        size_t start = 0;       // where the current fragment starts, size_t used for indices
        size_t pos;             // position of the found semicolon

        // searching for semicolons and cutting out subsequent fields
        while ((pos = line.find(';', start)) != string::npos) {
            data.push_back(line.substr(start, pos - start));
            start = pos + 1;    // shift start past the semicolon
        }
        data.push_back(line.substr(start)); // last field

        return Transaction(
            data[0],            // date
            data[1],            // category
            data[2],            // type
            stod(data[3]),      // amount (string → double)
            data[4]             // description
        );
    }
};
//--------------------------------------------------------------
//                        BUDGET CLASS
//--------------------------------------------------------------

class Budget {

    // Vector storing all transactions
    vector<Transaction> transactions;

public:

    // Adding a new transaction
    void add() {
        string d, c, t, desc;
        double amount;

        // Getting data from the user
        cout << "Date: ";
        cin >> d;
        cout << "Category: ";
        cin >> c;
        cout << "Type (income/expense): ";
        cin >> t;
        cout << "Amount: ";
        cin >> amount;
        cin.ignore(); // Removes the newline character from the buffer so getline works
        cout << "Description: ";
        getline(cin, desc); // getline is used to read the whole line instead of just the first word

        transactions.emplace_back(d, c, t, amount, desc); 
        // add a new element to the end of the list, constructing it from these data

        cout << "Added!\n"; // Info for the user
    }

    // Calculating and displaying the balance
    void showBalance() const {
        double balance = 0;

        for (const auto &t : transactions) { // checking whether it is an income or an expense
            if (t.getType() == "income") // t - object of the Transaction class
                balance += t.getAmount();
            else
                balance -= t.getAmount();
        }
        // Displays the balance with an assigned color
        cout << (balance >= 0 ? "\033[32m" : "\033[31m");
        cout << "Balance: " << fixed << setprecision(2) << balance << " PLN\n"; // fixed-point representation, 2 decimal places
        cout << "\033[0m"; // color reset
    }

    // Displaying all transactions
    void showAll() const {
        cout << left << setw(12) << "Date" // setwidth to x characters
             << setw(15) << "Category"
             << setw(12) << "Type"
             << setw(10) << "Amount"
             << setw(25) << "Description"
             << "\n";

        cout << string(74, '-') << endl;

        for (const auto &t : transactions) {// loop through all transactions
            string color = (t.getType() == "income") ? "\033[32m" : "\033[31m";// color depends on the type

            cout << left << setw(12) << t.getDate()
                 << setw(15) << t.getCategory()
                 << color << setw(12) << t.getType() << "\033[0m"
                 << right << setw(10) << fixed << setprecision(2) << t.getAmount()// fixed means as many decimal places as specified by setprecision
                 << "  "
                 << left << t.getDescription() << endl;
        }
    }

    // Saving data to a file
    void save() const {
        ofstream file("budget.txt");
        for (const auto &t : transactions)
            t.save(file);
        cout << "Saved.\n";
    }

    // Loading data from a file
    void load() {
        ifstream file("budget.txt");
        transactions.clear(); // clearing transactions, making room for new ones

        string line;
        while (getline(file, line)) // reads the line, saves it to a variable as long as it reads
            if (!line.empty()) // skips empty lines
                transactions.push_back(Transaction::fromLine(line));

        cout << "Loaded.\n";
    }
};


//--------------------------------------------------------------
//                           MAIN
//--------------------------------------------------------------

int main() {
    Budget budget; // budget object of the Budget class
    int choice;

    do { // displaying the menu
        cout << "\n----- HOME BUDGET -----"
                "\n1. Add"
                "\n2. Balance"
                "\n3. All"
                "\n4. Save"
                "\n5. Load"
                "\n0. Exit"
                "\n\nChoice: ";

        cin >> choice;

        switch (choice) { // user's choice
            case 1: budget.add(); break;
            case 2: budget.showBalance(); break;
            case 3: budget.showAll(); break;
            case 4: budget.save(); break;
            case 5: budget.load(); break;
            
            default: // Invalid choice
                if(choice < 0 || choice > 5){
                cout << "Please choose a number from the menu.\n";
                }
        }

    } while (choice != 0);

    return 0;
}