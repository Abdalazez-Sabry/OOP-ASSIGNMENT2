#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include<iostream>
#include"clientClass.h"

using namespace std;

class BankingApplication{

};

class BankAccount{
    private: 
        string accountID;
        double balance;
        Client* ptrClient;
    public:
        BankAccount(){balance = 0;};
        BankAccount(double amount){balance = amount;};
        double getBalance();
        void setBalance(double amount);
        string getID();
        void setID(string newID);
        void withdraw(double amount);
        void deposit(double amount );
        Client* setClient();
};

class SavingsBankAccount : public BankAccount{
    private:
        double minimumBalance;
    public:
        SavingsBankAccount(double initBalance = 0, double minBalance = 0);
        double getMinBalance();
        void setMinBalance(double amount);
        void virtual withdraw(double amount);
        void virtual deposit(double amount );
};


#endif