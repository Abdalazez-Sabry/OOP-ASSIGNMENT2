#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include<iostream>
#include<vector>
#include"clientClass.h"

using namespace std;

class Client;

class BankingApplication{
    private:
        vector<Client> clientsList;
        vector<BankAccount> accountsList;
        vector<SavingsBankAccount> savingsBankAccounts;
        vector<string> getNewAccountInputs();
        void printMenu();
        void withdraw();
        void deposit();
        int GetClientById(string accountId);
        void printAccountsInfo(Client client);
        
    public:
        BankingApplication();
        void createAccount();
        void listClients();
        void  mainMenuLoop();
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
        virtual void withdraw(double amount);
        virtual void deposit(double amount);
        void setClient(Client* client);
        Client* getClient();
};

class SavingsBankAccount : public BankAccount{
    private:
        double minimumBalance; 
    public:
        SavingsBankAccount(double , double);
        double getMinBalance();
        void setMinBalance(double amount);
        void  withdraw(double amount);
        void  deposit(double amount);
};


#endif