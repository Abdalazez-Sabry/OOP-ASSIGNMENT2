#include<iostream>
#include<string>
#include"BankSystem.h"

using namespace std;


SavingsBankAccount::SavingsBankAccount(double initBalance, double minBalance = 1000){
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

BankingApplication::BankingApplication(){
    clientsList.reserve(200);
    accountsList.reserve(200);
}

void BankingApplication::printMenu(){
    cout << "------------------------------------------" << endl;
    cout << "Welcome to FCAI Banking Application \n\n"<<
    "1. Create a New Account \n2. List Clients and Accounts \n3. Withdraw Money \n4. Deposit Money \n5. Exit \n\n" << 
    "Please Enter Choice =========> " ; 
}
void BankingApplication::createAccount(){
    enum accountsIfnoIndex{name, address, phoneNumber, accountType, balance, minimum};
    vector<string> accountsInfo = getNewAccountInputs();
    if (accountsInfo[balance].find_first_not_of("0123456789") ||accountsInfo[phoneNumber].find_first_not_of("0123456789") || accountsInfo[minimum].find_first_not_of("0123456789")){
        cout << "wrong account type" << endl;
        return;
    }
    if (accountsInfo[accountType] == "1"){
        BankAccount account(stod(accountsInfo[balance]));
        account.setID("FCAI-" + to_string(clientsList.size() +1));
        accountsList.push_back(account);
        Client newClient(accountsInfo[name], accountsInfo[address], accountsInfo[phoneNumber], &accountsList[accountsList.size()-1]);
        clientsList.push_back(newClient);

    }else if (accountsInfo[accountType] == "2"){
        SavingsBankAccount account(stod(accountsInfo[balance]), stod(accountsInfo[minimum]));
        account.setID("FCAI-" + to_string(clientsList.size() +1));
        accountsList.push_back(account);
        Client newClient(accountsInfo[name], accountsInfo[address], accountsInfo[phoneNumber], &accountsList[accountsList.size()-1]);
        clientsList.push_back(newClient);
    }else{
        cout << "wrong account type" << endl;
        return;
    }
    
    cout << "An account was created with ID " << clientsList[(clientsList.size()-1)].getBankAccount()->getID() <<
    " and Starting Balance " << accountsList[(accountsList.size() -1)].getBalance() << "L.E." << endl;
}

vector<string> BankingApplication::getNewAccountInputs(){
    string name, address, phoneNumber, accountType, balance, minimum;
    cout << "Please Enter Client Name =========> ";
    getline(cin>>ws, name);
    cout << "Please Enter Client Address =======> ";
    getline(cin>>ws, address);
    cout << "Please Enter Client Phone =======> ";
    getline(cin>>ws, phoneNumber);
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
    cin >> accountType;
    cout << "Please Enter the Starting Balance =========> ";
    cin >> balance;
    if (accountType == "2"){
        cout << "Please Enter the Minimum Balance =========> ";
        cin >> minimum;
    }
    return vector<string>{name, address, phoneNumber, accountType, balance, minimum};
}

void BankingApplication::listClients(){
    for(int i = 0; i < clientsList.size(); i++){
        cout << "-------------- " << clientsList[i].getName() << " --------------" << endl;
        cout << "Address: " << clientsList[i].getAdress() << endl;
        cout << "Phone: " << clientsList[i].getPhoneNumber() << endl;
        cout << "Balance: " << clientsList[i].getBankAccount()->getBalance() << endl;
        cout << clientsList[i].getBankAccount()->getID() << endl;
        cout << "------------------------------------------" << endl;
    }
}
void BankingApplication::withdraw(){
    string accountId, amount;
    Client client;
    cout << "Enter your account ID =========> ";
    cin >> accountId;
    int clientPos = GetClientById(accountId);
    if (clientPos == -1){
        cout << "There is no user with this ID";
        return;
    }
    client = clientsList[clientPos];
    printAccountsInfo(client);

    cout << "Enter the amount =========> ";
    cin >> amount;
    client.getBankAccount()->withdraw(stod(amount));

    printAccountsInfo(client);
}

void BankingApplication::deposit(){
    string accountId, amount;
    Client client;
    cout << "Enter your account ID =========> ";
    cin >> accountId;
    int clientPos = GetClientById(accountId);
    if (clientPos == -1){
        cout << "There is no user with this ID";
        return;
    }
    client = clientsList[clientPos];
    printAccountsInfo(client);

    cout << "Enter the amount =========> ";
    cin >> amount;
    client.getBankAccount()->deposit(stod(amount));

    printAccountsInfo(client);
}

void BankingApplication::printAccountsInfo(Client client){
    cout << "Logged in as " << client.getName() << endl;
    cout << "Account ID " << client.getBankAccount()->getID() << endl;
    cout << "Current balance " << client.getBankAccount()->getBalance() << endl;
}

int BankingApplication::GetClientById(string accountId){
    for (int i = 0; i < clientsList.size(); i++){
        if (clientsList[i].getBankAccount()->getID() == accountId){
            return i;
        }
    }
    return -1;
}

void BankingApplication::mainMenuLoop(){
    while (true){
        printMenu();
        string command;
        cin >> command;
        cout << "\n";
        if (command.size() > 1){
            cout << "Wrong input" << endl;
            continue;
        }
        switch (command[0]){
            case '1': createAccount(); break;
            case '2': listClients(); break;
            case '3': withdraw(); break;
            case '4': deposit(); break;
            case '5': return;
            default: cout << "Wrong input" << endl; 
        }
        cout << "\n";
    }
}

int main(){
    BankingApplication t;

    t.mainMenuLoop();
    
    // string lol =  "1140820411";
    // y.setBalance(10000);
    // Client nour("name", "october", lol, &y);
    // cout << nour.getAdress() << endl;
    // t.createAccount();
    // t.createAccount();
    // test.createAccount();
    // t.listClients();
    // cout << '\n' << t.clientsList[1].getBankAccount()->getID() << endl;
    
}