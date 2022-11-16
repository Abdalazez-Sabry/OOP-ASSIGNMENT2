#include<iostream>
#include<vector>

#include"BankAccount.h"

using namespace std;

double SavingsBankAccount::getMinimumBalance() {
	return this->minimumBalance;
}

void SavingsBankAccount::setMinimumBalance(double minimumBalance) {
	this->minimumBalance = minimumBalance;
}

SavingsBankAccount::SavingsBankAccount(double initBalance, double minBalance = 1000) {
    if (initBalance >= minBalance)
    {
        setBalance(initBalance);
        minimumBalance = minBalance;
    }
    else {
        cout << "\nThe initial balance can't be smaller than the minimum balance " << endl;
    }
}

void SavingsBankAccount::withdraw(double amount) {
    if (amount <= getBalance() && (getBalance() - amount) >= minimumBalance)
    {
        setBalance(getBalance() - amount);
    }
    else {
        cout << "Sorry, that's more than what you can withdraw " << endl;
    }
}
void SavingsBankAccount::deposit(double amount = 0) {
    if (amount >= 100)
    {
        setBalance(getBalance() + amount);
    }
    else {
        cout << "Sorry, you can't deposit that amount" << endl;
    }
}
