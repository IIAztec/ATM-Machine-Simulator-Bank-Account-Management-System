#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string green(const string& text) { // Function to make text green
    return "\033[32m" + text + "\033[0m";
}

string red(const string& text) { // Function to make text red
    return "\033[31m" + text + "\033[0m";
}

int IDgenerator() { // generates ID for new patient by reading the last line of the csv file and adding 1 to the ID
    ifstream accounts("/Users/ignatdanilin/Documents/University/Programming/ProjectExam/accounts.csv"); // Open the accounts.csv file to read the last account ID
    string line;
    string id;
    getline(accounts, line);
    while(getline(accounts, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
    }
    accounts.close();
    int newID = (stoi(id) + 1);
    return newID;
}

string hashingpass(string pass) { // hashing the password using djb2 algorithm
    unsigned long hash = 5381; // initializing the hash value to a large prime number
    for(char c : pass) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c, shifting the hash value to the left by 5 bits and adding the current character
    }
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hash; // converting the hash value to a hexadecimal string
    return ss.str(); // returning the hashed password as a string
}

void createNewAccount() { // Function to create a new account by taking user input and saving it to the accounts.csv file
    string firstname;
    string lastname;
    int pin;
    int confpin;
    cout << "------------------------\n";
    cout << "Enter your firs name: ";
    cin >> firstname;
    cout << "Enter your last name: ";
    cin >> lastname;
    string fullname = firstname + " " + lastname; // combining first name and last name to save in the accounts.csv file
    cout << "Create your pin(Max 6 digits): ";
    cin >> pin;
    cout << "Confirm your pin: ";
    cin >> confpin;
    if(pin == confpin && to_string(pin).length() <= 6) { // Validating the pin by checking if it matches the confirmation pin and is less than 6 digits
        int userID = IDgenerator(); // Generating a new account ID using the IDgenerator function
        ofstream account("/Users/ignatdanilin/Documents/University/Programming/ProjectExam/accounts.csv", ios::app); // opening the accounts.csv file in append mode to add a new line with the new account information
        account << userID << "," << fullname << "," << hashingpass(to_string(pin)) << "," << "100" << endl; // writing the new account information to the accounts.csv file, including the generated ID, full name, hashed pin and initial balance of 100
        cout << "------------------------\n";
        cout << green("Account created successuflly.\n");
        cout << "------------------------\n";
        account.close(); // closing the accounts.csv file after writing the new account information
    }
    else {
        cout << "------------------------\n";
        cout << red("Something went wrong. Try again.\n");
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        return createNewAccount(); // If the pin validation fails, the function calls itself recursively to allow the user to try again until they enter a valid pin.
    }
}

int main() {
    createNewAccount();
    return 0;
}