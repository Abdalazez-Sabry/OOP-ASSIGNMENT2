#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<vector>

using namespace std;

class BankAccount;
class SavingsBankAccount;

class Client {

private:
	string name;
	string address;
	string phoneNumber;
	BankAccount* ptrBankAccount;

public:
	string getName();

	string getAdress();

	string getPhoneNumber();

	BankAccount* getBankAccount();

	Client() = default;

	Client(string name, string address, string phonenumber, BankAccount* ptrBankAccount);
};

#endif
