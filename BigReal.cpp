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
        BigDecimalInt realNumber;
        int decimalPoint;
        void initalizeReal(string num);
        void removeSuffixZeros(BigDecimalInt& num);
        void removePrefixZeros(BigDecimalInt& num);
        void suffixZeros(BigDecimalInt & first, BigDecimalInt & second);
        void prefixZeros(BigDecimalInt & first, BigDecimalInt & second);
        BigReal calculation(BigReal anotherNumber);
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
    initalizeReal(num.getNumber());
}

BigReal::BigReal(string num){
    initalizeReal(num);
}
BigReal::BigReal(int num){
    initalizeReal(to_string(num));
}
BigReal::BigReal(double num){
    initalizeReal(to_string(num));
}

void BigReal::initalizeReal(string num){
    decimalPoint =num.size()- num.find(".");

    
    if (num.find(".") == -1)
    {
        realNumber = num;
        decimalPoint = 0;
        
    }else{
        decimalPoint =num.size()- num.find(".") -1; 
        num.erase(num.find("."),1);
        realNumber = num;
        removeSuffixZeros(realNumber);
    }
    removePrefixZeros(realNumber);
    // if (realNumber.getNumber ="")
}

// removes any unnecessary zeros at the beginning of the number  ex. 01 -> 1 
void BigReal::removePrefixZeros(BigDecimalInt& num){
    char newSign = (num.sign() == 1)? '+' : '-';
    string newNum =  num.getNumber(); 
    for (int i = 0; i < newNum.size() - decimalPoint-1; i++){ 
        if (newNum[i] == '0' ){
            newNum.erase(i, 1);
            i--;
        }
        else{
            break;
        }
    }
    num = (newSign + newNum);
}

// removes any unnecessary zeros at the end of the float part  ex. 1.10 -> 1.1
void BigReal::removeSuffixZeros(BigDecimalInt& num){
    // cout << " suffix " << num.getNumber() << " decipoint " << decimalPoint << endl;
    char newSign = (num.sign() == 1)? '+' : '-';
    string newNum = num.getNumber(); 
    int newDecimal = decimalPoint;
    for (int i = newNum.size() - 1; i > decimalPoint; i --){ 
        if (newNum[i] == '0'){
            newNum.erase(i, 1);
            newDecimal--;
        }
        else{
            break;
        }
    }
    // change this plese
    if (newNum == ""){
        newNum = "0";
    }
    decimalPoint = newDecimal;
    num = (newSign + newNum);
    
}

int BigReal::size(){
    int floatSize = (floatPart.getNumber() != "0")? floatPart.size() : 0;
    return intPart.size() + floatSize;
}

char BigReal::sign(){
    return (realNumber.sign() == 1)? '+' : '-';

}

string BigReal::getNumber(){
    string number = realNumber.getNumber();
    string minus = (sign() == '-')? "-" : "";

    if (decimalPoint != 0 && decimalPoint !=-1)
    {
        number.insert(number.size() - decimalPoint, ".");
    }
    return minus + number;
}
void BigReal::setNumber(string newNum){
    initalizeReal(newNum);
}

BigReal BigReal::operator+(BigReal anotherReal){

    return calculation(anotherReal);
}

BigReal BigReal:: operator-(BigReal anotherReal){
    char sign = (anotherReal.sign() == '+')? '-' : '+';
    string resultStr = anotherReal.realNumber.getNumber();
    resultStr.insert(resultStr.size() - anotherReal.decimalPoint, ".");
    anotherReal.setNumber(sign + resultStr);
    return calculation(anotherReal);
}


BigReal BigReal::calculation(BigReal anotherReal){
    BigDecimalInt realNumberCopy = realNumber;
    suffixZeros(realNumberCopy, anotherReal.realNumber);
    cout << realNumberCopy << " another real: " << anotherReal.realNumber << endl;

    BigReal result;
    BigDecimalInt resultDecimal = realNumberCopy + anotherReal.realNumber;
    char resultSign = (resultDecimal.sign() == 1)? '+' : '-';
    int resultDecimalPoint = (decimalPoint > anotherReal.decimalPoint)? decimalPoint : anotherReal.decimalPoint;
    string resultStr = resultDecimal.getNumber();
    resultStr.insert(resultStr.size() - resultDecimalPoint, ".");
    result.setNumber(resultSign + resultStr);
    return result;
}



bool BigReal::operator >(BigReal anotherReal){
    // suffixZeros(floatPart, anotherReal.floatPart);
    // if (sign() == '+' && anotherReal.sign() == '+')
    // {
    //     return this->isAbsBiggerThan(anotherReal);
    // }
    // else if (sign() == '-' && anotherReal.sign() == '-')
    // {
    //     return !this->isAbsBiggerThan(anotherReal);
    // }else if (sign() == '+' && anotherReal.sign() == '-')
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    suffixZeros(realNumber, anotherReal.realNumber);
    bool result = realNumber> anotherReal.realNumber;
    removeSuffixZeros(realNumber);
    removeSuffixZeros(anotherReal.realNumber);
    return result;
}
bool BigReal::operator <(BigReal anotherReal){
    suffixZeros(realNumber, anotherReal.realNumber);
    bool result = realNumber< anotherReal.realNumber;
    removeSuffixZeros(realNumber);
    removeSuffixZeros(anotherReal.realNumber);
    return result;
}

bool BigReal:: operator==(BigReal anotherReal){
    return (!(*this > anotherReal) && !(anotherReal > *this));
}


// compares between the absolute values of this number and another real number
bool BigReal::isAbsBiggerThan(BigReal anotherReal){
    prefixZeros(intPart, anotherReal.intPart);
    bool result = (intPart.getNumber() + floatPart.getNumber()) > (anotherReal.intPart.getNumber() + anotherReal.floatPart.getNumber());
    // removePrefixZeros();
    // anotherReal.removePrefixZeros();
    // removeSuffixZeros();
    return result;
}

// adds zeros at the end of the float part to help with calculations
void BigReal::suffixZeros(BigDecimalInt & first, BigDecimalInt & second){
    char firstSign = (first.sign() == 1)? '+' : '-';
    char secondSign = (second.sign() == 1)? '+' : '-';
     if (first.size() > second.size()){
        int difference = first.size() - second.size();
        string suffix (difference, '0');
        string tempSecond = secondSign + second.getNumber() + suffix;
        second = tempSecond;
    }else {
        int difference = second.size() - first.size();
        string suffix (difference, '0');
        string tempfirst = firstSign + first.getNumber() + suffix;
        first = tempfirst;
    }
}


// adds zeros at the beginning of the number
void BigReal::prefixZeros(BigDecimalInt & first, BigDecimalInt & second){
    
     if (first.size() > second.size()){
        int difference = first.size() - second.size();
        string prefix (difference, '0');
        string tempSecond = prefix + second.getNumber();
        second = tempSecond;
    }else {
        int difference = second.size() - first.size();
        string prefix (difference, '0');
        string tempfirst = prefix + first.getNumber();
        first = tempfirst;
    }
}

int main(){
    BigReal x("-0750.000");
    BigReal y("-500.5");
    BigReal z ("500.5");
    BigReal t("500.6");
    BigReal n("0");

    cout << x.getNumber() << y.getNumber() << endl;
    cout << (x>y) << " second " << (y<z) << " third "<< (z>t) << " fourth " << (n>x) << " fifth " << (n > z) << endl;
    cout << x.getNumber() << y.getNumber() << endl;

    // cout << y.getNumber() << " second " << x.getNumber() << endl;
    
    // cout << x.getNumber() << endl;
    // z = x - y;
    // cout << z.getNumber() << endl << " y: " << x.getNumber();
}