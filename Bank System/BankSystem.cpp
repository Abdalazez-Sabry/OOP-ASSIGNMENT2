#include<iostream>
#include<string>
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
    // cout << "hello " << balance << endl;
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
void BankAccount::setClient(Client* client){
    ptrClient = client;
}
Client* BankAccount::getClient(){
    return ptrClient;
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

Client::Client(string name, string address, string phoneNumber, BankAccount* ptrBankAccount){
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
    this->ptrBankAccount = ptrBankAccount;
    ptrBankAccount->setClient(this);
    cout << "test " << ptrBankAccount->getBalance() << endl;
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


void BankingApplication::printMenu(){
    cout << "Welcome to FCAI Banking Application \n"<<
    "1. Create a New Account \n2. List Clients and Accounts \n3. Withdraw Money \n4. Deposit Money \n5. Exit \n" << 
    "Please Enter Choice =========> " ; 
}
void BankingApplication::createAccount(){
    string name, address, phonenumber;
    int accountType;
    double balance;
    cout << "Please Enter Client Name =========> ";
    getline(cin>>ws, name);
    cout << "Please Enter Client Address =======> ";
    getline(cin>>ws, address);
    cout << "Please Enter Client Phone =======> ";
    getline(cin>>ws, phonenumber);
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
    cin >> accountType;
    cout << "Please Enter the Starting Balance =========> ";
    cin >> balance;
    if (accountType == 1)
    {

        BankAccount account(balance);
        account.setID("FCAI-" + to_string(clientsList.size() +1));
        accountsList.push_back(account);
        Client newClient(name, address, phonenumber, &accountsList[accountsList.size()-1]);
        clientsList.push_back(newClient);
    }else if (accountType == 2)
    {
        double minimum;
        cout << "Please Enter the Minimum Balance =========> ";
        cin >> minimum;
        SavingsBankAccount account(balance, minimum);
        account.setID("FCAI-" + to_string(clientsList.size() +1));
        accountsList.push_back(account);
        Client newClient(name, address, phonenumber, &accountsList[accountsList.size()-1]);
        clientsList.push_back(newClient);
        
    }
    cout << "An account was created with ID " << clientsList[(clientsList.size()-1)].getBankAccount()->getID() <<
    " and Starting Balance " << accountsList[(accountsList.size() -1)].getBalance() << " L.E." << endl;
}
void BankingApplication::listClients(){
    for(int i = 0; i < clientsList.size(); i++){
        cout << "-------------- " << clientsList[i].getName() << " --------------" << endl;
        cout << "Address: " << clientsList[i].getAdress() << endl;
        cout << "Phone: " << clientsList[i].getPhoneNumber() << endl;
        cout << "Balance: " << clientsList[i].getBankAccount()->getBalance() << endl;
        cout << clientsList[i].getBankAccount()->getID() << endl;
    }
}



int main(){
    SavingsBankAccount y;
    BankingApplication t;
    
    // string lol =  "1140820411";
    // y.setBalance(10000);
    // Client nour("name", "october", lol, &y);
    // cout << nour.getAdress() << endl;
    t.createAccount();
    t.createAccount();
    // test.createAccount();
    t.listClients();
    cout << '\n' << t.clientsList[0].getBankAccount()->getID() << endl;
    
}