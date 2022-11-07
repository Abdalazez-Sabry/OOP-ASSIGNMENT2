#include<iostream>
#include"BankSystem.h"

using namespace std;


SavingsBankAccount::SavingsBankAccount(double initBalance, double minBalance){
    if (initBalance >= minBalance)
    {
        setBalance(initBalance);
        minimumBalance = minBalance;
    }else{
        cout << "\nThe initial balance can't be smaller than the minimum balance " << endl;
    }
}


double BankAccount::getBalance(){
    return balance;
}
void BankAccount::setBalance(double amount){
    balance = amount;
}
string BankAccount::getID(){
    return accountID;
}
void BankAccount::setID(string newID){
    accountID = newID;
}
double SavingsBankAccount::getMinBalance(){
    return minimumBalance;
}
void SavingsBankAccount::setMinBalance(double amount){
    if (amount >= 0)
    {
        minimumBalance = amount;
    }else{
        cout << "Sorry, the minimum balance can't be a negative number" << endl;
    }
}


void BankAccount::withdraw(double amount){
    if (amount <= balance)
    {
        balance -= amount;
    }else{
    cout << "\t--Error cannot withdraw " << amount << " from the account--\n" << endl;
    }
    
}
void BankAccount::deposit(double amount){
    if (amount >= 0)
    {
        balance += amount;
    }else{
        cout << "Sorry, you can't deposit a negative amount" << endl;
    }
}

void SavingsBankAccount::withdraw(double amount){
    if (amount <= getBalance() && (getBalance() - amount) >= minimumBalance)
    {
        setBalance(getBalance() - amount);
    }else{
        cout << "Sorry, that's more than what you can withdraw " << endl;
    }
}
void SavingsBankAccount::deposit(double amount = 0){
    if (amount >= 100)
    {
        setBalance(getBalance() + amount);
    }else{
        cout << "Sorry, you can't deposit that amount" << endl;
    }
}

string Client::getName(){
    return name;
}
string Client::getAdress(){
    return address;
}
string Client::getPhoneNumber(){
    return phoneNumber;
}
BankAccount* Client::getBankAccount(){
    return ptrBankAccount;
}

int main(){
    SavingsBankAccount y;
    string lol =  "1140820411";
    y.setBalance(10000);
    Client nour("name", "october", lol, &y);
    cout << nour.ptrBankAccount->getBalance();
    }