// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 2
// Program Name: BigReal
// Last Modification Date: 31/10/2022
// Author1 and ID and Group: Abdalazez Sabry Abdalazez  ID: 20210212 (a, b, c)
// Author2 and ID and Group: Karim Mohamed Mohsen  ID: 20210509
// Author3 and ID and Group: Ayman  ID: 20210517 (f, i, j , k)
/*
description: In this problem we developed a new C++ type (class).
that can hold unlimited real values and performs operations on them.
such as: +, -, <, > and ==.
 */


#include <iostream>
#include <string>
#include <sstream>
#include "BigDecimalIntClass.cpp"

using namespace std;

class BigReal{
    private:
        BigDecimalInt intPart;
        BigDecimalInt floatPart;
        void sperateIntAndFloat(string num);
        void removeSuffixZeros();
        void removePrefixZeros();
        void suffixZeros(BigDecimalInt & first, BigDecimalInt & second);
        BigReal addition(BigReal anotherNumber);
        BigReal subtraction(BigReal anotherReal);
        BigReal decideOperation(BigReal anotherDec);
        bool isAbsBiggerThan(BigReal anotherReal);
        
    
    public:
        BigReal(){}
        BigReal(BigDecimalInt num);
        BigReal(string num);
        BigReal(int num);
        BigReal(double num);
        string getNumber();
        void setNumber(string newNum);
        int size();
        char sign();
    
    
        BigReal operator+(const BigReal anotherReal);
        BigReal operator-(const BigReal anotherReal);
        bool operator >(BigReal anotherReal);
        bool operator <(BigReal anotherReal);
        bool operator==(BigReal anotherReal);
};

BigReal::BigReal(BigDecimalInt num){
    sperateIntAndFloat(num.getNumber());
}

BigReal::BigReal(string num){
    sperateIntAndFloat(num);
}
BigReal::BigReal(int num){
    sperateIntAndFloat(to_string(num));
}
BigReal::BigReal(double num){
    sperateIntAndFloat(to_string(num));
}


// seperates between the fraction part of the number and the iteger part into two different BigDecimalInts
void BigReal::sperateIntAndFloat(string num){

    int decimalPointPos = num.find(".");

    if (decimalPointPos == -1){
        intPart = BigDecimalInt(num);
        floatPart = BigDecimalInt("0");
    }else{
        intPart = num.substr(0, decimalPointPos);
        floatPart = num.substr(decimalPointPos + 1);
        removePrefixZeros();
        removeSuffixZeros();
    }

}

// removes any unnecessary zeros at the beginning of the number  ex. 01 -> 1 
void BigReal::removePrefixZeros(){
    string f = intPart.getNumber(); 
    for (int i = 0; i < f.size()-1; i++){
        cout << f[i] << endl;
        if (f[i] == '0'){
            
            f.erase(i, 1);
            i--;
        }
        else{
            break;
        }
    }
    intPart.setNumber(f);
}

// removes any unnecessary zeros at the end of the float part  ex. 1.10 -> 1.1
void BigReal::removeSuffixZeros(){
    string f = floatPart.getNumber(); 
    for (int i = f.size() - 1; i > 0; i --){
        if (f[i] == '0'){
            f.erase(i, 1);
        }
        else{
            break;
        }
    }
    floatPart.setNumber(f);
}

int BigReal::size(){
    int floatSize = (floatPart.getNumber() != "0")? floatPart.size() : 0;
    return intPart.size() + floatSize;
}

char BigReal::sign(){
    return (intPart.sign() == 1)? '+' : '-';

}

string BigReal::getNumber(){
    string minus = (sign() == '-')? "-" : "";
    return minus + intPart.getNumber() + "." + floatPart.getNumber();
}
void BigReal::setNumber(string newNum){
    sperateIntAndFloat(newNum);
}

BigReal BigReal::operator+(BigReal anotherReal){

    return decideOperation(anotherReal);
}

BigReal BigReal:: operator-(BigReal anotherReal){
    char sign = (anotherReal.sign() == '+')? '-' : '+';
    anotherReal = (sign + anotherReal.intPart.getNumber()) + '.' + anotherReal.floatPart.getNumber();
    return decideOperation(anotherReal);
}

BigReal BigReal::decideOperation(BigReal anotherReal){
            if (sign() == anotherReal.sign()){
                return addition(anotherReal);
            }
            else {
                return subtraction(anotherReal);
            }
        }

BigReal BigReal::addition(BigReal anotherReal){

    BigDecimalInt sumOfFloat, sumOfInt;
    sumOfInt = intPart + anotherReal.intPart;

    suffixZeros(floatPart, anotherReal.floatPart);

    sumOfFloat = floatPart + anotherReal.floatPart;

    char sign = (sumOfInt.sign() == 1) ? '+' : '-';

    if (sumOfFloat.size() > floatPart.size())
    {
        sumOfFloat = sumOfFloat.getNumber().substr(1);
        sumOfInt =(BigDecimalInt)"1" + (BigDecimalInt)sumOfInt.getNumber();
    }
    return BigReal(sign + sumOfInt.getNumber() + '.' + sumOfFloat.getNumber());

}

BigReal BigReal::subtraction(BigReal anotherReal){
    BigDecimalInt subOfFloat, subOfInt;

    BigReal big , small;
    big = (this->isAbsBiggerThan(anotherReal))? *this : anotherReal;
    small = (this->isAbsBiggerThan(anotherReal))? anotherReal : *this;

    char sign = big.sign();

    big.intPart = (BigDecimalInt)big.intPart.getNumber();
    small.intPart = (BigDecimalInt)small.intPart.getNumber();

    if (big.floatPart < small.floatPart)
    {
        big.floatPart.setNumber("1" + big.floatPart.getNumber());
        big.intPart = (BigDecimalInt)big.intPart.getNumber() - (BigDecimalInt)"1";
    }
    
    subOfFloat = big.floatPart - small.floatPart;

    subOfInt = big.intPart - small.intPart;

    return BigReal(sign + subOfInt.getNumber() + '.' + subOfFloat.getNumber());


} 

bool BigReal::operator >(BigReal anotherReal){
    suffixZeros(floatPart, anotherReal.floatPart);
    if (sign() == '+' && anotherReal.sign() == '+')
    {
        return this->isAbsBiggerThan(anotherReal);
    }
    else if (sign() == '-' && anotherReal.sign() == '-')
    {
        return !this->isAbsBiggerThan(anotherReal);
    }else if (sign() == '+' && anotherReal.sign() == '-')
    {
        return true;
    }
    // (sign() == '-' && anotherReal.sign() == '+')
    else
    {
        return false;
    }
}
bool BigReal::operator <(BigReal anotherReal){
    return !(*this > anotherReal);
}

bool BigReal:: operator==(BigReal anotherReal){
    return (!(*this > anotherReal) && !(anotherReal > *this));
}


// compares between the absolute values of this number and another real number
bool BigReal::isAbsBiggerThan(BigReal anotherReal){
 return (intPart.getNumber() + floatPart.getNumber()) > (anotherReal.intPart.getNumber() + anotherReal.floatPart.getNumber());
}

// adds zeros at the end of the float part to help with calculations
void BigReal::suffixZeros(BigDecimalInt & first, BigDecimalInt & second){
    
     if (first.size() > second.size()){
        int difference = first.size() - second.size();
        string suffix (difference, '0');
        string tempSecond = second.getNumber() + suffix;
        second = tempSecond;
    }else {
        int difference = second.size() - first.size();
        string suffix (difference, '0');
        string tempfirst = first.getNumber() + suffix;
        first = tempfirst;
    }
}
int main(){
    BigReal x("-+123");
    cout << x.getNumber();
    BigReal y("7.5");




}