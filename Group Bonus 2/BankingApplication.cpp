#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include "BankingApplication.h"

using namespace std;

BankingApplication::BankingApplication() {
    clientsList.reserve(20);
    accountsList.reserve(20);
    savingsBankAccounts.reserve(20);
}

void BankingApplication::printMenu() {
    cout << "------------------------------------------" << endl;
    cout << "Welcome to FCAI Banking Application \n\n" <<
        "1. Create a New Account \n2. List Clients and Accounts \n3. Withdraw Money \n4. Deposit Money \n5. Exit \n\n" <<
        "Please Enter Choice =========> ";
}
void BankingApplication::createAccount() {
    enum accountsIfnoIndex { name, address, phoneNumber, accountType, balance, minimum };
    vector<string> accountsInfo = getNewAccountInputs();


    if (accountsInfo[balance].find_first_not_of("0123456789") != string::npos || accountsInfo[phoneNumber].find_first_not_of("0123456789") != string::npos || accountsInfo[minimum].find_first_not_of("0123456789") != string::npos) {
        cout << "wrong account type" << endl;
        return;
    }
    if (accountsInfo[accountType] == "1") {
        BankAccount account(stod(accountsInfo[balance]));
        account.setID("FCAI-" + to_string(clientsList.size() + 1));
        accountsList.push_back(account);

        Client newClient(accountsInfo[name], accountsInfo[address], accountsInfo[phoneNumber], &accountsList[accountsList.size() - 1]);
        clientsList.push_back(newClient);

        cout << "An account was created with ID " << clientsList[(clientsList.size() - 1)].getBankAccount()->getID() <<
            " and Starting Balance " << fixed << setprecision(0) << accountsList[(accountsList.size() - 1)].getBalance() << "L.E." << endl;

    }
    else if (accountsInfo[accountType] == "2") {
        cout << "test : " << (accountsInfo[balance] < accountsInfo[minimum]) << endl;
        if (stod(accountsInfo[balance]) < stod(accountsInfo[minimum])) {
            cout << "the balance cannot be less than the minimum balance " << endl;
            return;
        }
        SavingsBankAccount account(stod(accountsInfo[balance]), stod(accountsInfo[minimum]));
        account.setID("FCAI-" + to_string(clientsList.size() + 1));
        savingsBankAccounts.push_back(account);

        Client newClient(accountsInfo[name], accountsInfo[address], accountsInfo[phoneNumber], &savingsBankAccounts[savingsBankAccounts.size() - 1]);
        clientsList.push_back(newClient);

        cout << "An account was created with ID " << clientsList[(clientsList.size() - 1)].getBankAccount()->getID() <<
            " and Starting Balance " << fixed << setprecision(0) << savingsBankAccounts[(savingsBankAccounts.size() - 1)].getBalance() << "L.E." << endl;
    }
    else {
        cout << "wrong account type" << endl;
        return;
    }

}

vector<string> BankingApplication::getNewAccountInputs() {
    string name, address, phoneNumber, accountType, balance, minimum;
    cout << "Please Enter Client Name =========> ";
    getline(cin >> ws, name);
    cout << "Please Enter Client Address =======> ";
    getline(cin >> ws, address);
    cout << "Please Enter Client Phone =======> ";
    getline(cin >> ws, phoneNumber);
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
    cin >> accountType;
    cout << "Please Enter the Starting Balance =========> ";
    cin >> balance;
    if (accountType == "2") {
        cout << "Please Enter the Minimum Balance =========> ";
        cin >> minimum;
    }
    return vector<string>{name, address, phoneNumber, accountType, balance, minimum};
}

void BankingApplication::listClients() {
    for (int i = 0; i < clientsList.size(); i++) {
        cout << "-------------- " << clientsList[i].getName() << " --------------" << endl;
        cout << "Address: " << clientsList[i].getAdress() << endl;
        cout << "Phone: " << clientsList[i].getPhoneNumber() << endl;
        cout << "Balance: " << fixed << setprecision(0) << clientsList[i].getBankAccount()->getBalance() << endl;
        cout << "ID: " << clientsList[i].getBankAccount()->getID() << endl;
        cout << "------------------------------------------" << endl;
    }
}
void BankingApplication::withdraw() {
    string accountId, amount;
    Client client;
    cout << "Enter your account ID =========> ";
    cin >> accountId;
    int clientPos = GetClientById(accountId);
    if (clientPos == -1) {
        cout << "There is no user with this ID";
        return;
    }
    client = clientsList[clientPos];
    printAccountsInfo(client);

    cout << "Enter the amount =========> ";
    cin >> amount;
    client.getBankAccount()->withdraw(stod(amount));

    printAccountsInfo(client);
}

void BankingApplication::deposit() {
    string accountId, amount;
    Client client;
    cout << "Enter your account ID =========> ";
    cin >> accountId;
    int clientPos = GetClientById(accountId);
    if (clientPos == -1) {
        cout << "There is no user with this ID";
        return;
    }
    client = clientsList[clientPos];
    printAccountsInfo(client);

    cout << "Enter the amount =========> ";
    cin >> amount;
    client.getBankAccount()->deposit(stod(amount));

    printAccountsInfo(client);
}

void BankingApplication::printAccountsInfo(Client client) {
    cout << "Logged in as " << client.getName() << endl;
    cout << "Account ID " << client.getBankAccount()->getID() << endl;
    cout << "Current balance " << client.getBankAccount()->getBalance() << endl;
}

int BankingApplication::GetClientById(string accountId) {
    for (int i = 0; i < clientsList.size(); i++) {
        if (clientsList[i].getBankAccount()->getID() == accountId) {
            return i;
        }
    }
    return -1;
}

void BankingApplication::mainMenuLoop() {
    while (true) {
        printMenu();
        string command;
        cin >> command;
        cout << "\n";
        if (command.size() > 1) {
            cout << "Wrong input" << endl;
            continue;
        }
        switch (command[0]) {
        case '1': createAccount(); break;
        case '2': listClients(); break;
        case '3': withdraw(); break;
        case '4': deposit(); break;
        case '5': return;
        default: cout << "Wrong input" << endl;
        }
        cout << "\n";
    }
}