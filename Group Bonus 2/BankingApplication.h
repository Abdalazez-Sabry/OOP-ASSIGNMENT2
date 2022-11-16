#ifndef BANKINGAPPLICATION_H
#define BANKINGAPPLICATION_H
#include<vector>
#include<iostream>

using namespace std;

#include"BankAccount.h"
// #include"SavingsBankAccount.h"
#include"Client.h"

class BankingApplication {

private:
	vector<Client> clientsList;
	vector<BankAccount> accountsList;
	vector<SavingsBankAccount> savingsBankAccounts;

	
	void printMenu();

	void withdraw();

	void deposit();

	int GetClientById(string accountId);

	void printAccountsInfo(Client client);

	vector<string> getNewAccountInputs();

public:

	BankingApplication();

	void createAccount();

	void listClients();

	void mainMenuLoop();
};

#endif
