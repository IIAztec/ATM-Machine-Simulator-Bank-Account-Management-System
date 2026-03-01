#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string hashingpass(string pass) { // hashing the password using djb2 algorithm
    unsigned long hash = 5381; // initializing the hash value to a large prime number
    for(char c : pass) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c, shifting the hash value to the left by 5 bits and adding the current character
    }
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hash; // converting the hash value to a hexadecimal string
    return ss.str(); // returning the hashed password as a string
}

string green(const int& number) { // Function to make text green
    return "\033[32m" + to_string(number) + "\033[0m";
}

string red(const string& text) { // Function to make text red
    return "\033[31m" + text + "\033[0m";
}

struct Transaction { // Struct for saving files in CSV file
    string transactionType;
    string accountID;
    int previousBalance;
    int newBalance;
    int amount;
};

struct UserAccount { // User struct to work with ATM
    string accountID;
    string username;
    string password;
    int balance;
    string adminID;
    string adminName;
    string adminPassword;

    void writeTransactionLog(const Transaction& log) { // Saving transaction log to file
        ofstream database("database.csv", ios::app); // Open the database.csv file in append mode to add a new line with the transaction log information
        database << log.accountID << ","
                 << log.transactionType << ","
                 << log.previousBalance << ","
                 << log.newBalance << ","
                 << log.amount << "\n";
        database.close(); // Close the file after writing to it
    }

    void updateAccountFile() { // Function to update account file after transactions
        ifstream readFile("accounts.csv");
        ofstream createTemp("temp.csv");
        string line;
        while (getline(readFile, line)) { // Read original file
            stringstream ss(line);
            string accountID, username, password, balance;
            getline(ss, accountID, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balance, ',');
            if (accountID == this->accountID) { // If the account ID matches - update balance
                createTemp << accountID << "," << username << "," << password << "," << this->balance << "\n";
            }
            else {
                createTemp << line << "\n"; // If not - write the same data
            }
        }
        readFile.close();
        createTemp.close();
        remove("accounts.csv");
        rename("temp.csv", "accounts.csv");
        createTemp.close();
    }

    void checkIDENG() { // Function to check account ID
        ifstream accounts("accounts.csv"); // Open the accounts.csv file to read the account information
        string logID;
        string logPassword;
        cout << "Enter your account ID: ";
        cin >> logID;
        cout << "Enter your password: ";
        cin >> logPassword;
        accounts.clear(); // clear flag
        accounts.seekg(0, ios::beg); // change flag
        string line;
        string accountID, username, password, balance;
        getline(accounts, line); // Skip header
        while(getline(accounts, line)) { // Read CSV file
            stringstream ss(line);
            getline(ss, accountID, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balance, ',');
            if ((hashingpass(logPassword) == password) && (logID == accountID)) { // Check ID and password to login in account(from CSV)
                this->accountID = accountID;
                this->username = username;
                this->password = password;
                this->balance = stoi(balance);
                cout << "--------------------------\n";
                cout << "Login successful. Welcome " << username << "\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                accounts.close(); // Close the file after reading
                return menuENG();
            }
        }
        // Validation
        cout << "------------------------\n";
        cout << red("Invalid ID or password.\n");
        cout << "Please try again.\n";
        cout << "------------------------\n";
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        accounts.close(); // Close the file after reading
        return checkIDENG();
    }

    void checkIDRUS() { // Function to check account ID
        ifstream accounts("accounts.csv"); // Open the accounts.csv file to read the account information
        string logID;
        string logPassword;
        cout << "Введите ваш аккаунтИД: ";
        cin >> logID;
        cout << "Введите ваш пароль: ";
        cin >> logPassword;
        accounts.clear(); // clear flag
        accounts.seekg(0, ios::beg); // change flag
        string line;
        string accountID, username, password, balance;
        getline(accounts, line); // Skip header
        while(getline(accounts, line)) { // Read CSV file
            stringstream ss(line);
            getline(ss, accountID, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balance, ',');
            if ((hashingpass(logPassword) == password) && (logID == accountID)) { // Check ID and password to login in account(from CSV)
                this->accountID = accountID;
                this->username = username;
                this->password = password;
                this->balance = stoi(balance);
                cout << "--------------------------\n";
                cout << "Вход выполнен успешно. Добро пожаловать, " << username << "\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                accounts.close(); // Close the file after reading
                return menuRUS();
            }
        }
        // Validation
        cout << "------------------------\n";
        cout << red("Неверный аккаунтИД или пароль.\n");
        cout << "Попробуйте снова.\n";
        cout << "------------------------\n";
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        accounts.close(); // Close the file after reading
        return checkIDRUS();
    }

    void checkIDDE() { // Function to check account ID
        ifstream accounts("accounts.csv"); // Open the accounts.csv file to read the account information
        string logID;
        string logPassword;
        cout << "Geben Sie Ihre Konto-ID ein: ";
        cin >> logID;
        cout << "Geben Sie Ihr Passwort ein: ";
        cin >> logPassword;
        accounts.clear(); // clear flag
        accounts.seekg(0, ios::beg); // change flag
        string line;
        string accountID, username, password, balance;
        getline(accounts, line); // Skip header
        while(getline(accounts, line)) { // Read CSV file
            stringstream ss(line);
            getline(ss, accountID, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balance, ',');
            if ((hashingpass(logPassword) == password) && (logID == accountID)) { // Check ID and password to login in account(from CSV)
                this->accountID = accountID;
                this->username = username;
                this->password = password;
                this->balance = stoi(balance);
                cout << "--------------------------\n";
                cout << "Eingeloggt als: " << username << "\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                accounts.close(); // Close the file after reading
                return menuDE();
            }
        }
        // Validation
        cout << "------------------------\n";
        cout << red("Ungültige Konto-ID oder Passwort.\n");
        cout << "Bitte versuchen Sie es erneut.\n";
        cout << "------------------------\n";
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        accounts.close(); // Close the file after reading
        return checkIDDE();
    }

    void menuENG() { // Function to display account information
        int UserChoice;
        cout << "------------------------\n";
        cout << "Account ID: " << accountID << "\n";
        cout << "Username: " << username << "\n";
        cout << "Balance: " << green(balance) << "€" << "\n";
        cout << "What would you like to do?\n1. Deposit\n2. Withdraw\n3. Exit\nEnter the number: ";
        cin >> UserChoice;

        switch (UserChoice) { // Menu with user input
        case 1:
            depositENG();
            menuENG();
            break;
        case 2:
            withdrawENG();
            menuENG();
            break;
        case 3:
            cout << "------------------------\n";
            cout << "Goodbye!" << "\n";
            exit(0);
            break;
        default: // Wrong input validation
            cout << "\n";
            cout << "------------------------\n";
            cout << red("Invalid input.\n");
            cout << "Go back to main menu.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            return menuENG();
        }
    }

    void menuRUS() { // Function to display account information
        int UserChoice;
        cout << "------------------------\n";
        cout << "АккаунтИД: " << accountID << "\n";
        cout << "Имя пользователя: " << username << "\n";
        cout << "Баланс: " << green(balance) << "€" << "\n";
        cout << "Что бы вы хотели сделать?\n1. Пополнить\n2. Снять\n3. Выйти\nВведите номер: ";
        cin >> UserChoice;

        switch (UserChoice) {
        case 1:
            depositRUS();
            menuRUS();
            break;
        case 2:
            withdrawRUS();
            menuRUS();
            break;
        case 3:
            cout << "------------------------\n";
            cout << "До свидания!" << "\n";
            exit(0);
            break;
        default: // Wrong input validation
            cout << "\n";
            cout << "------------------------\n";
            cout << red("Неверный ввод.\n");
            cout << "Возвращаемся в главное меню.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            return menuRUS();
        }
    }

    void menuDE() { // Function to display account information
        int UserChoice;
        cout << "------------------------\n";
        cout << "Konto-ID: " << accountID << "\n";
        cout << "Benutzername: " << username << "\n";
        cout << "Kontostand: " << green(balance) << "€" << "\n";
        cout << "Was möchten Sie tun?\n1. Einzahlen\n2. Abheben\n3. Beenden\nGeben Sie die Nummer ein: ";
        cin >> UserChoice;

        switch (UserChoice) {
        case 1:
            depositDE();
            menuDE();
            break;
        case 2:
            withdrawDE();
            menuDE();
            break;
        case 3:
            cout << "------------------------\n";
            cout << "Auf Wiedersehen!" << "\n";
            exit(0);
            break;
        default: // Wrong input validation
            cout << "\n";
            cout << "------------------------\n";
            cout << red("Ungültige Eingabe.\n");
            cout << "Zurück zum Hauptmenü.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            return menuDE();
        }
    }

    void withdrawENG() { // Function to withdraw money
        cout << "------------------------\n";
        cout << "How much would you like to withdraw? ";
        double amount;
        cin >> amount;
        if (amount > balance || amount < 5) {
            if (amount > balance) {
            
            cout << "------------------------\n";
            cout << red("Not enough balance to withdraw. ") << green(amount) << "€" << "\n";
            }
            else {
            cout << "------------------------\n";
            cout << red("The minimum withdraw amount is ") << green(5) << red("€") << "\n";
            }
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance -= amount;
            cout << "------------------------\n";
            cout << "Withdrawal of " << green(amount) << "€ successful. New balance: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "withdrawal";
            tempData.accountID = accountID;
            tempData.previousBalance = balance + amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void withdrawRUS() { // Function to withdraw money
        cout << "------------------------\n";
        cout << "Сколько бы вы хотели снять? ";
        double amount;
        cin >> amount;
        if (amount > balance || amount < 5) {
            if (amount > balance) {
            cout << "------------------------\n";
            cout << red("Недостаточно средств на счету для снятия. ") << green(amount) << "€" << "\n";
            }
            else {
                cout << "------------------------\n";
                cout << red("Минимальная сумма для снятия ") << green(5) << red("€") << "\n";
            }
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance -= amount;
            cout << "------------------------\n";
            cout << "Снятие " << green(amount) << "€ прошло успешно. Новый баланс: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "withdrawal";
            tempData.accountID = accountID;
            tempData.previousBalance = balance + amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void withdrawDE() { // Function to withdraw money
        cout << "------------------------\n";
        cout << "Wie viel möchten Sie abheben? ";
        double amount;
        cin >> amount;
        if (amount > balance || amount < 5) {
            if (amount > balance) {
            cout << "------------------------\n";
            cout << red("Nicht genug Guthaben, um ") << green(amount) << "€" << red(" abzuheben.\n");
            }
            else {
                cout << "------------------------\n";
                cout << red("Mindestauszahlungsbetrag ") << green(5) << red("€") << "\n";
            }
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance -= amount;
            cout << "------------------------\n";
            cout << "Abhebung von " << green(amount) << "€ erfolgreich. Neuer Kontostand: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "withdrawal";
            tempData.accountID = accountID;
            tempData.previousBalance = balance + amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void depositENG() { // Function to deposit money
        cout << "------------------------\n";
        cout << "How much would you like to deposit? ";
        double amount;
        cin >> amount;
        if (amount < 5) {
            cout << "------------------------\n";
            cout << red("The minimum deposit amount is ") << green(5) << red(" euro.") << "\n";
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance += amount;
            cout << "--------------------------\n";
            cout << "Deposit of " << green(amount) << "€ successful. New balance: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "deposit";
            tempData.accountID = accountID;
            tempData.previousBalance = balance - amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void depositRUS() { // Function to deposit money
        cout << "------------------------\n";
        cout << "Сколько вы хотите внести? ";
        double amount;
        cin >> amount;
        if (amount < 5) {
            cout << "------------------------\n";
            cout << red("Минимальная сумма пополнения ") << green(5) << red("€") << "\n";
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance += amount;
            cout << "--------------------------\n";
            cout << "Внесение " << green(amount) << "€ прошло успешно. Новый баланс: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "deposit";
            tempData.accountID = accountID;
            tempData.previousBalance = balance - amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void depositDE() { // Function to deposit money
        cout << "------------------------\n";
        cout << "Wie viel möchten Sie einbezahlen? ";
        double amount;
        cin >> amount;
        if (amount < 5) {
            cout << "------------------------\n";
            cout << red("Mindesteinzahlung ") << green(5) << red("€") << "\n";
        }
        else {
            amount = floor(amount); // Round down to the nearest whole number
            balance += amount;
            cout << "--------------------------\n";
            cout << "Einbezahlen von " << green(amount) << "€ erfolgreich. Neuer Kontostand: " << green(balance) << "€" << "\n";
            Transaction tempData; // Log transaction data
            tempData.transactionType = "deposit";
            tempData.accountID = accountID;
            tempData.previousBalance = balance - amount;
            tempData.newBalance = balance;
            tempData.amount = amount;
            writeTransactionLog(tempData); // Write transaction log to file
            updateAccountFile(); // Update account file after transaction
        }
    }

    void writeTransactionLogAdmin(const Transaction& log) { // Saving transaction log to file
        ofstream database("database.csv", ios::app); // Open the database.csv file to read the transaction log information
        database << log.accountID << ","
                 << log.transactionType << ","
                 << log.previousBalance << ","
                 << log.newBalance << ","
                 << log.amount << "\n";
        database.close(); // Close the file after writing to it
    }

    void checkAdminID() { // Function to check admin ID
        ifstream adminAccount("admindata.csv"); // Open the admindata.csv file to read the admin account information
        string logID;
        string logPassword;
        cout << "------------------------\n";
        cout << "Enter your Admin ID: ";
        cin >> logID;
        cout << "Enter your Admin Password: ";
        cin >> logPassword;
        adminAccount.clear(); // clear flag
        adminAccount.seekg(0, ios::beg); // change flag
        string line;
        string adminID, adminName, adminPassword;
        getline(adminAccount, line); // Skip header
        while(getline(adminAccount, line)) {
            stringstream ss(line);
            getline(ss, adminID, ',');
            getline(ss, adminName, ',');
            getline(ss, adminPassword, ',');
            if ((hashingpass(logPassword) == adminPassword) && (logID == adminID)) {
                this->adminID = adminID;
                this->adminName = adminName;
                this->adminPassword = adminPassword;
                cout << "--------------------------\n";
                cout << "Admin Login successful. Welcome " << adminName << "\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                adminAccount.close(); // Close the file after reading
                return adminMenu();
            }
        }
        cout << "------------------------\n";
        cout << red("Invalid Admin ID or Password.\n");
        cout << "Please try again.\n";
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        adminAccount.close(); // Close the file after reading
        return checkAdminID();
    }

    void adminMenu() {
        cout << "------------------------\n";
        cout << "What would you like to do?\n1. Check Account Details\n2. Manage User Balances\n3. Exit\nEnter the number: ";
        int adminChoice;
        cin >> adminChoice;
        
        switch (adminChoice) {
            case 1:
                checkAccountDetails();
                break;
            case 2:
                manageUserBalances();
                break;
            case 3:
                cout << "------------------------\n";
                cout << "Goodbye Admin!" << "\n";
                exit(0);
                break;
            default:
                cout << "------------------------\n";
                cout << red("Invalid input.\n");
                cout << "Go back to admin menu.\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                return adminMenu();
        }
    }

    void checkAccountDetails() {
        ifstream accounts("accounts.csv"); // Open the accounts.csv file to read the account information
        string searchID;
        cout << "------------------------\n";
        cout << "Enter the Account ID: ";
        cin >> searchID;
        accounts.clear(); // clear flag
        accounts.seekg(0, ios::beg); // change flag
        string line;
        string accountID, username, password, balance;
        getline(accounts, line); // Skip headaer
        while(getline(accounts, line)) {
            stringstream ss(line);
            getline(ss, accountID, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balance, ',');
            if (searchID == accountID) {
                cout << "------------------------\n";
                cout << "Account ID: " << accountID << "\n";
                cout << "Username: " << username << "\n";
                cout << "Balance: " << green(stoi(balance)) << "€" << "\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                accounts.close(); // Close the file after reading
                return adminMenu();
            }
        }
        cout << "------------------------\n";
        cout << red("Account not found.\n");
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        accounts.close(); // Close the file after reading
        return adminMenu();
    }

    void manageUserBalances() {
        ifstream accounts("accounts.csv"); // Open the accounts.csv file to read the account information
        UserAccount user1;
        UserAccount user2;
        string searchID;
        string searchIDS;
        cout << "------------------------\n";
        cout << "Enter the Account ID to take money from: ";
        cin >> searchID;
        string line;
        string accountID, username, password, balance;
        double amount;
        getline(accounts, line); // Skip header
        while(getline(accounts, line)) {
            stringstream ss(line);
            string balanceStr;
            getline(ss, user1.accountID, ',');
            getline(ss, user1.username, ',');
            getline(ss, user1.password, ',');
            getline(ss, balanceStr, ',');
            user1.balance = stoi(balanceStr);
            if (searchID == user1.accountID) {
                cout << "------------------------\n";
                cout << "Account Details:\n";
                cout << "Account ID: " << user1.accountID << "\n";
                cout << "Username: " << user1.username << "\n";
                cout << "Balance: " << green(user1.balance) << "€" << "\n";
                cout << "Enter the Account ID to give money to: ";
                cin >> searchIDS;
                accounts.clear(); // clear flag
                accounts.seekg(0, ios::beg); // change flag
                getline(accounts, line); // Skip header
                while(getline(accounts, line)) {
                    stringstream ss(line);
                    string balanceStr2;
                    getline(ss, user2.accountID, ',');
                    getline(ss, user2.username, ',');
                    getline(ss, user2.password, ',');
                    getline(ss, balanceStr2, ',');
                    user2.balance = stoi(balanceStr2);
                    if (searchIDS == user2.accountID) {
                        cout << "------------------------\n";
                        cout << "Enter the amount to transfer from " << user1.username << " to " << user2.username << ": ";
                        cin >> amount;
                        if ((amount <= user1.balance) && (amount > 0)) {
                            user1.balance -= amount;
                            user2.balance += amount;
                            cout << "--------------------------\n";
                            cout << "Transfer successful.\n";
                            cout << "Go back to admin menu.\n";
                            cout << user1.username << " new balance: " << green(user1.balance) << "€" << "\n";
                            cout << user2.username << " new balance: " << green(user2.balance) << "€" << "\n";
                            Transaction adminLog;
                            adminLog.accountID = user1.accountID;
                            adminLog.transactionType = "adminTransaction";
                            adminLog.previousBalance = user1.balance + amount;
                            adminLog.newBalance = user1.balance;
                            adminLog.amount = amount;
                            writeTransactionLogAdmin(adminLog); // Log for user1
                            user1.updateAccountFile(); // Update account file after transaction
                            Transaction adminLog2;
                            adminLog2.accountID = user2.accountID;
                            adminLog2.transactionType = "adminTransaction";
                            adminLog2.previousBalance = user2.balance - amount;
                            adminLog2.newBalance = user2.balance;
                            adminLog2.amount = amount;
                            writeTransactionLogAdmin(adminLog2); // Log for user2
                            user2.updateAccountFile(); // Update account file after transaction
                            accounts.clear(); // clear flag
                            accounts.seekg(0, ios::beg); // change flag
                            accounts.close(); // Close the file after reading
                            return adminMenu();
                        }
                        else {
                            cout << "--------------------------\n";
                            cout << red("Wrong amount.\n");
                            cout << "Go back to admin menu.\n";
                            cout << "--------------------------\n";
                            accounts.clear(); // clear flag
                            accounts.seekg(0, ios::beg); // change flag
                            accounts.close(); // Close the file after reading
                            return adminMenu();
                        }
                    }
                }
                // Validation
                cout << "--------------------------\n";
                cout << red("Account is not found.\n");
                cout << "Go back to admin menu.\n";
                cout << "--------------------------\n";
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                accounts.clear(); // clear flag
                accounts.seekg(0, ios::beg); // change flag
                accounts.close(); // Close the file after reading
                return adminMenu();
            }
        }
        // Validation
        cout << "--------------------------\n";
        cout << red("Account is not found.\n");
        cout << "Go back to admin menu.\n";
        cout << "--------------------------\n";
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        accounts.clear(); // clear flag
        accounts.seekg(0, ios::beg); // change flag
        accounts.close(); // Close the file after reading
        return adminMenu();
    }
};

void callmenu() {
    int menuChoice;
    cout << "------------------------\n";
    cout << "Select language / Выберите язык / Sprache auswählen.\n";
    cout << "1. English\n";
    cout << "2. Русский\n";
    cout << "3. Deutsch\n";
    cout << "4. Admin Login(English only)\n";
    cout << "5. Exit / Выход / Beenden\n";
    cout << "Enter the number / Введите номер / Nummer eingeben: ";
    cin >> menuChoice;

    switch (menuChoice) {
        case 1: {
            UserAccount user;
            user.checkIDENG();
            break;
        }
        case 2: {
            UserAccount user;
            user.checkIDRUS();
            break;
        }
        case 3: {
            UserAccount user;
            user.checkIDDE();
            break;
        }
        case 4: {
            UserAccount admin;
            admin.checkAdminID();
            break;
        }
        case 5: {
            cout << "------------------------\n";
            cout << "Goodbye! / До свидания! / Auf Wiedersehen!" << "\n";
            break;
        }
        default: {
            cout << "------------------------\n";
            cout << red("Invalid input.\n");
            cout << red("Неверный ввод.\n");
            cout << red("Ungültige Eingabe.\n");
            cout << "Please try again / Попробуйте снова / Bitte versuchen Sie es erneut.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            return callmenu();
        }    
    }
}

int main() {
    callmenu();
    return 0;
}