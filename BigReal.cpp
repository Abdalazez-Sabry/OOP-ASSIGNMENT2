// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 2
// Program Name: BigReal
// Last Modification Date: 31/10/2022
// Author1 and ID and Group: Abdalazez Sabry Abdalazez  ID: 20210212 (a, b, c)
// Author2 and ID and Group: Karim Mohamed Mohsen  ID: 20210509
// Author3 and ID and Group: Ayman Mohammed Aboukhalifa  ID: 20210517 (f, i, j , k)
/*
description: In this problem we developed a new C++ type (class).
that can hold unlimited real values and performs operations on them.
such as: +, -, <, > and ==.
 */


#include <iostream>
#include <string>
#include <sstream>
//#include "BigReal.h"
#include "BigDecimalIntClass.cpp"

using namespace std;

class BigReal{
    private:
        BigDecimalInt realNumber;
        int decimalPoint;
        void initalizeReal(string num);
        char getBigDecimalSign(BigDecimalInt b);
        void removeSuffixZeros(BigDecimalInt& num);
        void removePrefixZeros(BigDecimalInt& num);
        void removeSignIfZero();
        void addSuffixZeros(BigReal & first, BigReal & second);
        string fillZerosToDecimalPoint(string str, int decimalPoint);
        
    public:
        BigReal(){}
        BigReal(BigDecimalInt num);
        BigReal(string num);
        BigReal(int num);
        BigReal(double num);

        string getNumber();
        void setNumber(BigDecimalInt newNum);
        void setNumber(int newNum);
        void setNumber(double newNum);
        void setNumber(string newNum);
        int size();
        char sign();
    
        BigReal sum(BigReal anotherNumber);
        BigReal operator+(const BigReal anotherReal);
        BigReal operator-(const BigReal anotherReal);
        bool operator >(BigReal anotherReal);
        bool operator <(BigReal anotherReal);
        bool operator==(BigReal anotherReal);
        friend ostream& operator << (ostream& out, BigReal num);
        friend istream& operator >> (istream& in, BigReal& num);
};

BigReal::BigReal(BigDecimalInt num){
    char sign = getBigDecimalSign(num);
    initalizeReal(sign + num.getNumber());
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
    int dotPos = num.find(".");
    decimalPoint = num.size() - dotPos - 1; 

    if (stod(num) == 0){
        realNumber = BigDecimalInt("0");
        decimalPoint = 0;
    }
    else if (dotPos == -1){
        
        realNumber = num;
        decimalPoint = 0;
    }else if(decimalPoint == 0){
        num.erase(dotPos, 1);
        realNumber = num;
    }else{
        num.erase(dotPos, 1);
        realNumber = num;
        removeSuffixZeros(realNumber);
    }
    removePrefixZeros(realNumber);

    removeSignIfZero();
}

// removes any unnecessary zeros at the beginning of the number  ex. 01 -> 1 
void BigReal::removePrefixZeros(BigDecimalInt& num){
    char newSign = getBigDecimalSign(realNumber);
    string newNum =  num.getNumber(); 
    // cout << "newNum " << newNum << " decimal " << decimalPoint << endl;
    for (int i = 0; i < newNum.size() - decimalPoint-1; i++){ 
        if (newNum[i] == '0' && newNum.size() >1){
            newNum.erase(i, 1);
            i--;
            // cout << " test " << newNum << endl;
        }
        else{
            break;
        }
    }
    num = (newSign + newNum);
}
// removes any unnecessary zeros at the end of the float part  ex. 1.10 -> 1.1
void BigReal::removeSuffixZeros(BigDecimalInt& num){
    char newSign = getBigDecimalSign(realNumber);
    string newNum = num.getNumber(); 
    int newDecimal = decimalPoint;
    for (int i = newNum.size() - 1; i >= newDecimal; i --){ 
        if (newNum[i] == '0'){
            newNum.erase(i, 1);
            newDecimal--;
            if (newDecimal == 0){
                break;
            }
        }
        else{
            break;
        }
    }
    decimalPoint = newDecimal;
    num.setNumber(newSign + newNum);
    
}
void BigReal::removeSignIfZero(){
    if (realNumber.getNumber() == "0"){
        realNumber.setNumber("0");
    }
}

int BigReal::size(){
    return realNumber.size();
}
char BigReal::sign(){
    return getBigDecimalSign(realNumber);
}
char BigReal::getBigDecimalSign(BigDecimalInt b){
    return (b.sign() == 1)? '+' : '-';
}

string BigReal::getNumber(){
    string number = realNumber.getNumber();
    string putMinusIfNegative = (sign() == '-')? "-" : "";
    if (decimalPoint != 0){
        number.insert(number.size() - decimalPoint, ".");
    }
    return putMinusIfNegative + number;
}
void BigReal::setNumber(BigDecimalInt newNum){
    char sign = getBigDecimalSign(newNum);
    initalizeReal(sign + newNum.getNumber());
}
void BigReal::setNumber(int newNum){
    initalizeReal(to_string(newNum));
}
void BigReal::setNumber(double newNum){
    initalizeReal(to_string(newNum));
}
void BigReal::setNumber(string newNum){
    initalizeReal(newNum);
}

BigReal BigReal::operator+(BigReal anotherReal){
    return sum(anotherReal);
}

BigReal BigReal:: operator-(BigReal anotherReal){
    // change anotherReal sign then send it to sum
    char sign = (getBigDecimalSign(anotherReal.realNumber) == '+')? '-':'+' ;
    string resultStr = anotherReal.realNumber.getNumber();
    resultStr.insert(resultStr.size() - anotherReal.decimalPoint, ".");
    anotherReal.setNumber(sign + resultStr);

    return sum(anotherReal);
}


BigReal BigReal::sum(BigReal anotherReal){
    BigReal thisCopy (*this), result;
    addSuffixZeros(thisCopy, anotherReal);

    BigDecimalInt resultDecimal = thisCopy.realNumber + anotherReal.realNumber;
    char resultSign = getBigDecimalSign(resultDecimal);
    int resultDecimalPoint = (thisCopy.decimalPoint > anotherReal.decimalPoint)? thisCopy.decimalPoint : anotherReal.decimalPoint;

    string resultStr = resultDecimal.getNumber();
    resultStr = fillZerosToDecimalPoint(resultStr, resultDecimalPoint);
    resultStr.insert(resultStr.size() - resultDecimalPoint, ".");

    result.setNumber(resultSign + resultStr);
    // cout << "test " <<endl;
    return result;
}
string BigReal::fillZerosToDecimalPoint(string str, int decimalPoint){
    while (decimalPoint > str.size() - 1){
        str.insert(0, "0");
    }

    return str;
}

bool BigReal::operator>(BigReal anotherReal){
    BigReal thisCopy (*this);
    addSuffixZeros(thisCopy, anotherReal);
    return thisCopy.realNumber > anotherReal.realNumber;
}
bool BigReal::operator<(BigReal anotherReal){
    BigReal thisCopy (*this);
    addSuffixZeros(thisCopy, anotherReal);
    return thisCopy.realNumber < anotherReal.realNumber;
}
bool BigReal:: operator==(BigReal anotherReal){
    return (!(*this > anotherReal) && !(anotherReal > *this));
}

// adds zeros at the end of the float part to help with calculations
void BigReal::addSuffixZeros(BigReal & first, BigReal & second){
    BigReal& big = (first.decimalPoint > second.decimalPoint)? first : second;
    BigReal& small = (first.decimalPoint > second.decimalPoint)? second : first;

    int difference = big.decimalPoint - small.decimalPoint;
    string suffix(difference, '0');
    small.realNumber = small.sign() + small.realNumber.getNumber() + suffix;
}

ostream& operator << (ostream& out, BigReal num)
{
    out << num.getNumber();
    return out;
}

istream& operator >> (istream& in, BigReal& num)
{
    string s;
    in >> s;
    num.setNumber(s);
    return in;
}
//  int main(){
// //     BigReal x("-0750.000");
// //     BigReal y("-500.5");
// //     BigReal z ("500.5");
// //     BigReal t("-500.5");
// //     BigReal n("0");
// cout << "hello" << endl;
//     // cout << n.getNumber() << endl;
//     // cout << (t+n).getNumber() << endl;

//     // cout << x.getNumber() << y.getNumber() << endl;
//     // cout << (x>y) << " second " << (y<z) << " third "<< (z>t) << " fourth " << (n>x) << " fifth " << (n > z) << endl;
//     // cout << x.getNumber() << y.getNumber() << endl;
//     // cout << x.getNumber() << y.getNumber() << endl;
//     // cout << (x>y) << " second " << (y<z) << " third "<< (z>t) << " fourth " << (n>x) << " fifth " << (n > z) << endl;
//     // cout << x.getNumber() << y.getNumber() << endl;

//     // cout << y.getNumber() << " second " << x.getNumber() << endl;

//     // cout << x.getNumber() << endl;
//     // z = x - y;
//     // cout << z.getNumber() << endl << " y: " << x.getNumber();
//     // cout << x.getNumber() << endl;
//     //z = x-x;
//     //cout << z.getNumber() << endl;
// }