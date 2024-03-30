
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class BankAccount {
private:
    int AccNum;
    string AccType;
    string AccOwner;
    int Balance;

public:
    BankAccount(int num) {
        AccNum = num;
        cout << "Enter Account Type: ";
        cin >> AccType;
        cout << "Enter Account Owner: ";
        cin >> AccOwner;
        cout << "Enter Initial Balance: ";
        cin >> Balance;
    }

    void SaveToFile() {
        ofstream file("bank_accounts.txt", ios::app);

        if (file.is_open()) {
            file << "AccountNumber: " << AccNum << "\n"
                 << "AccountType: " << AccType << "\n"
                 << "AccountOwner:" << AccOwner << "\n"
                 << "AccountBalance: " << Balance << "\n\n";
            file.close();
            cout << "Bank account information saved to file." << endl;
        } else {
            cerr << "Error opening file." << endl;
        }
    }

    static int GetLastCount() {
        ifstream file("last_count.txt");
        int lastCount = 0;

        if (file.is_open()) {
            file >> lastCount;
            file.close();
        }

        return lastCount;
    }

    static void UpdateLastCount(int count) {
        ofstream file("last_count.txt", ios::out);

        if (file.is_open()) {
            file << count;
            file.close();
        }
    }

    static void show_account_info_file() {
        ifstream f("bank_accounts.txt");

        if (f.is_open())
            cout << f.rdbuf();
    }

    static void search_throught_Data(string desiretext) {
        ifstream f("bank_accounts.txt");

        if (f.is_open()) {
            string line;
            while (getline(f, line)) {
                if (line.find(desiretext) != string::npos) {
                    cout << line << endl;
                    for (int i = 0; i < 4 && getline(f, line); ++i) {
                        cout << line << endl;
                    }
                }
            }
            f.close();
        }
    }

    static void Deposit(string owner_name, int amount) {
        ifstream f("bank_accounts.txt");
        int Balance = 0;
        if (f.is_open()) {
            string Line;
            while (getline(f, Line)) {
                if (Line.find("AccountOwner:" + owner_name) != string::npos) {
                    while (getline(f, Line)) {
                        if (Line.find("AccountBalance:") != string::npos) {
                            istringstream iss(Line);
                            string word;
                            iss >> word; // Read "Account Balance:"
                            iss >> Balance; // Read the balance value
                            break;
                        }
                    }
                    break;
                }
            }
            f.close();
        }

        if (Balance != 0) {
            Balance += amount;
            ifstream file("bank_accounts.txt", ios::in | ios::out);
            if (file.is_open()) {
                string line;
                string newContent;
                while (getline(file, line)) {
                    if (line.find("AccountOwner: " + owner_name) != string::npos) {
                        newContent += "AccountBalance: " + to_string(Balance) + "\n";
                    } else {
                        newContent += line + "\n";
                    }
                }
                file.close();
                ofstream outFile("bank_accounts.txt");
                outFile << newContent;
                outFile.close();
                cout << owner_name << "'s account balance updated. New balance is: " << Balance << endl;
            } else {
                cerr << "Error opening file." << endl;
            }
        } else {
             cout << owner_name << "'s account balance not found." << endl;
         }
    }

    static void Withdraw(string owner_name, int amount) {
        ifstream f("bank_accounts.txt");
        int Balance = 0;
        if (f.is_open()) {
            string Line;
            while (getline(f, Line)) {
                if (Line.find("AccountOwner: " + owner_name) != string::npos) {
                    while (getline(f, Line)) {
                        if (Line.find("AccountBalance: ") != string::npos) {
                            istringstream iss(Line);
                            string word;
                            iss >> word; // Read "Account Balance:"
                            iss >> Balance; // Read the balance value
                            break;
                        }
                    }
                    break;
                }
            }
            f.close();
        }

        if (Balance != 0) {
            if (Balance >= amount) {
                Balance -= amount;
                ifstream file("bank_accounts.txt", ios::in | ios::out);
                if (file.is_open()) {
                    string line;
                    string newContent;
                    while (getline(file, line)) {
                        if (line.find("AccountOwner: " + owner_name) != string::npos) {
                            newContent += "AccountBalance: " + to_string(Balance) + "\n";
                        } else {
                            newContent += line + "\n";
                        }
                    }
                    file.close();
                    ofstream outFile("bank_accounts.txt");
                    outFile << newContent;
                    outFile.close();
                    cout << owner_name << "'s account balance updated. New balance is: " << Balance << endl;
                } else {
                    cerr << "Error opening file." << endl;
                }
            } else {
                cout << "Insufficient balance for withdrawal." << endl;
            }
        } else {
            cout << owner_name << "'s account balance not found." << endl;
        }
    }
};

void DisplayMenu();


int main() {
    char ch;
    int count = BankAccount::GetLastCount();
    do {
        DisplayMenu();
        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int count = BankAccount::GetLastCount() + 1;
                BankAccount account(count);
                account.SaveToFile();
                BankAccount::UpdateLastCount(count);
                break;
            }
            case 2: {
                BankAccount::show_account_info_file();
                break;
            }
            case 3: {
                cout << "Enter the desire text : ";
                string desiretext;
                cin >> desiretext;
                BankAccount::search_throught_Data(desiretext);
                break;
            }
            case 4: {
                cout << "Select one choice : (1->Deposit, 2->Withdraw)";
                int opt;
                cin >> opt;
                switch (opt) {
                    case 1: {
                        cout << "Input owner Name :";
                        string Owner_name;
                        cin >> Owner_name;
                        int amount;
                        cout << "Enter the amount to deposit: ";
                        cin >> amount;
                        BankAccount::Deposit(Owner_name, amount);
                        break;
                    }
                    case 2: {
                        cout << "Input owner Name :";
                        string Owner_name;
                        cin >> Owner_name;
                        int amount;
                        cout << "Enter the amount to withdraw: ";
                        cin >> amount;
                        BankAccount::Withdraw(Owner_name, amount);
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                }
                break;
            }
            case 5: {
                cout << "Exiting program.\n";
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        cout << "Wanna do this process again ? (Y/N) : ";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
    cout<<"Thank for using This App";
    cin.ignore();
    return 0;
}

void DisplayMenu() {
    cout << "\nBank Account Management System\n";
    cout << "1. Add a new bank account\n";
    cout << "2. Show Account data\n";
    cout << "3. Search Data\n";
    cout << "4. Deposit/Witdraw \n";
    cout << "5. Exit\n";
}
