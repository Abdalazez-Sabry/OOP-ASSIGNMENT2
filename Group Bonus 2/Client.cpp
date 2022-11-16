#include<iostream>
#include<vector>
#include "Client.h"
#include"BankAccount.h"

using namespace std;
class BankAccount;

Client::Client(string name, string address, string phoneNumber, BankAccount* ptrBankAccount) {
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->ptrBankAccount = ptrBankAccount;
    ptrBankAccount->setClient(this);
}

string Client::getName() {
    return name;
}
string Client::getAdress() {
    return address;
}
string Client::getPhoneNumber() {
    return phoneNumber;
}
BankAccount* Client::getBankAccount() {
    return ptrBankAccount;
}