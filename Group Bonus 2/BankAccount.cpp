#include<iostream>
#include<vector>

#include "BankAccount.h"

using namespace std;
BankAccount::BankAccount() {
	balance = 0;
	ptrClient = nullptr;
}

BankAccount::BankAccount(double amount) : balance(amount){}

double BankAccount::getBalance() {
	return this->balance;
}

void BankAccount::setBalance(double balance) {
	this->balance = balance;
}

string BankAccount::getID() {
	return this->accountID;
}

void BankAccount::setID(string accountID) {
	this->accountID = accountID;
}

void BankAccount::withdraw(double amount) {
    if (amount <= balance)
    {
        balance -= amount;
    }
    else {
        cout << "\t--Error cannot withdraw " << amount << " from the account--\n" << endl;
    }

}
void BankAccount::deposit(double amount) {
    if (amount >= 0)
    {
        balance += amount;
    }
    else {
        cout << "Sorry, you can't deposit a negative amount" << endl;
    }
}

void BankAccount::setClient(Client* client) {
    ptrClient = client;
}
Client* BankAccount::getClient() {
    return ptrClient;
}
