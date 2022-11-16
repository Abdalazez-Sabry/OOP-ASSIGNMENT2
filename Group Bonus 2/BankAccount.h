#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include<iostream>
using namespace std;

class Client;

class BankAccount {

protected:
	string accountID;
	Client* ptrClient;
	double balance;

public:
	BankAccount();

	BankAccount(double amount);

	double getBalance();

	void setBalance(double balance);

	string getID();

	void setID(string accountID);

	virtual void withdraw(double amount);

	virtual void deposit(double amount);

	Client* getClient();

	void setClient(Client* ptrClient);
};

class SavingsBankAccount :public BankAccount {

public:
	double minimumBalance;

	double getMinimumBalance();

	void setMinimumBalance(double minimumBalance);

	SavingsBankAccount(double balance, double minimumBalance);

	void withdraw(double amount);

	void deposit(double amount);
};

#endif
