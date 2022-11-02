#include<iostream>

using namespace std;

class BankingApplication{

};

class BankAccount : public BankingApplication{
    private: 
        string accountID;
        double balance;
    public:
        BankAccount(){balance = 0;};
        BankAccount(double amount){balance = amount;};
        double getBalance();
        void setBalance(double amount);
        string getID();
        void setID(string newID);
        void withdraw(double amount);
        void deposit(double amount );
};
class SavingsBankAccount : public BankAccount{
    private:
        double minimumBalance;
    public:
        SavingsBankAccount(double initBalance = 0, double minBalance = 0);
        double getMinBalance();
        void setMinBalance(double amount);
        void withdraw(double amount);
        void deposit(double amount );
};


SavingsBankAccount::SavingsBankAccount(double initBalance, double minBalance){
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the inital balance --> " ;
        cin >> initBalance;
        cout << "Please enter the minimum balance --> "; 
        cin >> minBalance;
        if (initBalance >= minBalance)
        {
            setBalance(initBalance);
            minimumBalance = minBalance;
            breakLoop = true;
        }else{
            cout << "\nThe initial balance can't be smaller than the minimum balance " << endl;
        }
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
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the minimum balance  --> ";
        cin >> amount;
        if (amount >= 0)
        {
            minimumBalance = amount;
            breakLoop = true;
        }else{
            cout << "Sorry, the minimum balance can't be a negative number" << endl;
        }
        
    }
}


void BankAccount::withdraw(double amount = 0){
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the amount to withdraw --> ";
        cin >> amount;
        if (amount <= balance)
        {
            balance -= amount;
            breakLoop = true;
        }else{
            cout << "Sorry, that's more than what you can withdraw " << endl;
        }
        
    }
    
}
void BankAccount::deposit(double amount = 0){
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the amount to deposit --> ";
        cin >> amount;
        if (amount >= 0)
        {
            balance += amount;
            breakLoop = true;
        }else{
            cout << "Sorry, you can't deposit a negative amount" << endl;
        }
        
    }
}
void SavingsBankAccount::withdraw(double amount = 0){
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the amount to withdraw --> ";
        cin >> amount;
        if (amount <= getBalance() && (getBalance() - amount) >= minimumBalance)
        {
            setBalance(getBalance() - amount);
            breakLoop = true;
        }else{
            cout << "Sorry, that's more than what you can withdraw " << endl;
        }
        
    }
    
}
void SavingsBankAccount::deposit(double amount = 0){
    bool breakLoop = false;
    while (!breakLoop)
    {
        cout << "Please enter the amount to deposit --> ";
        cin >> amount;
        if (amount >= 100)
        {
            setBalance(getBalance() + amount);
            breakLoop = true;
        }else{
            cout << "Sorry, you can't deposit that amount" << endl;
        }
        
    }
}



int main(){
    BankAccount y;
    BankAccount x(250);
    // cout << x.getBalance() << endl << y.getBalance() << endl;
    SavingsBankAccount t;
    t.deposit();
    cout << t.getBalance() << endl;
    t.withdraw();
    cout << t.getBalance();
}