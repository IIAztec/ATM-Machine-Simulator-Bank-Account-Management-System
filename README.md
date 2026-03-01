# ATM Machine Simulator / Bank Account Management System

Console application that simulates an ATM machine and allows users to manage their bank accounts. 
Users can register, log in, view their balance, deposit and withdraw money. 
Admins can log in to manage users' balances.

## Features

### For Users:
- **Account registration** (via separate program `createUserAcc.cpp`)
- Login with password (PIN) authentication
- View current balance
- Deposit funds (minimum 5 euros)
- Withdraw funds (minimum 5 euros, cannot exceed balance)
- Multi-language support: **English**, **Russian**, **German**
- Transaction history

### For Administrators:
- Admin login with special credentials
- View any user's account information
- Transfer funds between user accounts
- Log of all admin actions

## Security
- **Passwords (PINs) are never stored in plain text!**
- PINs are hashed using the **djb2 algorithm** before storage
- During login, the entered PIN is hashed and compared to the stored hash
- All transactions are logged for auditing

## Technologies
- **Programming Language:** C++
- **Libraries used:**
  - `iostream` – input/output operations
  - `string` – string manipulation
  - `cstdlib` – general utilities
  - `fstream` – file handling
  - `sstream` – string streams
  - `iomanip` – output formatting (for hash conversion to hex)

## Data Storage
All data is stored in **CSV files**:

- `accounts.csv` – user data  
  (ID, full name, **PIN hash**, balance)  
- `admindata.csv` – admin data  
  (ID, name, **password hash**)
- `database.csv` – transaction log  
  (account ID, transaction type, previous balance, new balance, amount)

## System Requirements
- C++11 compatible compiler
- Terminal with **ANSI color support** (for green and red text)

## Compilation and Execution

### Main ATM Program (`atm.cpp`)
```bash
# Compile
g++ -std=c++11 atm.cpp -o atm

# Run (Linux/macOS)
./atm

# Run (Windows)
atm.exe
```
### Account Creation Tool (`createUserAcc.cpp`)
*This separate program allows new users to register. It must be run **before** using the ATM with a new account.*
*During registration, the user provides **first name**, **last name**, and a **PIN** (max 6 digits).*
*The PIN is **hashed** and stored together with a newly generated **ID** and an initial balance of 100.*
```bash
# Compile
g++ -std=c++11 createUserAcc.cpp -o createUserAcc

# Run (Linux/macOS)
./createUserAcc

# Run (Windows)
createUserAcc.exe
```
## Project Structure
```bash
atm.cpp               # Main ATM simulator
createUserAcc.cpp     # Standalone account registration tool
accounts.csv          # User database
admindata.csv         # Admin database
database.csv          # Transaction log
README.md             # Documentation
atm                   # Compiled executable (Linux/macOS)
createUserAcc         # Compiled executable (Linux/macOS)
atm.exe               # Compiled executable (Windows)
createUserAcc.exe     # Compiled executable (Windows)
```
## Author

**Ignat Danilin**
- GitHub: [@IIAztec](https://github.com/IIAztec)
- Email: danilin.ignat@gmail.com

*Student at SRH University Stuttgart*
