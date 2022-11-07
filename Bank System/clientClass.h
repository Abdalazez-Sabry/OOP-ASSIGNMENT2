#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include"BankSystem.h"

using namespace std;

class Client{
    public:
        string name;
        string address;
        string phoneNumber;
        BankAccount* ptrBankAccount; 
    public:
        Client(string name, string adreess, string phoneNumber, BankAccount* ptrBankAccount){
            this->name = name;
            this->address = address;
            this->phoneNumber = phoneNumber;
            this->ptrBankAccount = ptrBankAccount;
        }
        string getName();
        string getAdress();
        string getPhoneNumber();
        BankAccount* getBankAccount();

};

#endif