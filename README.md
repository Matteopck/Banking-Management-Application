Bank Account Management System

This program allows users to create and manage bank accounts. It provides the following features:

--Features
Add a new bank account: Users can create a new bank account by providing the account type, owner name, and initial balance.
Show account data: The program can display all the account information stored in the bank_accounts.txt file.
Search data: Users can search for specific account information by entering a desired text. The program will display all account details containing the search text.
Deposit/Withdraw:
Deposit: Users can deposit an amount into an existing account by providing the account owner's name and the deposit amount.
Withdraw: Users can withdraw an amount from an existing account by providing the account owner's name and the withdrawal amount. The withdrawal will only be successful if the account has sufficient balance.
Exit: Users can exit the program.

--Usage
Compile the C++ source code using a C++ compiler.
Run the compiled executable.
The program will display a menu with various options. Enter the corresponding number to perform the desired operation.
Follow the on-screen prompts to provide the required information (e.g., account type, owner name, balance, deposit/withdrawal amount).
The program will perform the requested operation and display the result.
After each operation, the program will ask if you want to perform another operation. Enter 'Y' or 'y' to continue, or any other key to exit.

--Implementation Details
The program uses a BankAccount class to represent a bank account and perform various operations.
Account information is stored in a text file named bank_accounts.txt.
The last_count.txt file keeps track of the last assigned account number to ensure unique account numbers for new accounts.
The program uses file input/output operations to read and write account data to the respective files.

--Dependencies
This program requires a C++ compiler and the standard C++ libraries (iostream, fstream, sstream).
