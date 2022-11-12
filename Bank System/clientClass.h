#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include"BankSystem.h"

using namespace std;

class BankAccount;

class Client{
    private:
        string name;
        string address;
        string phoneNumber;
        BankAccount* ptrBankAccount; 
    public:
        Client(){}
        Client(string name, string address, string phoneNumber, BankAccount* ptrBankAccount);
        string getName();
        string getAdress();
        string getPhoneNumber();
        BankAccount* getBankAccount();

};

#endif