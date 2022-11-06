#ifndef BIGREAL_H
#define BIGREAL_H

#include "BigDecimalIntClass.h"

class BigReal{
    private:
        BigDecimalInt intPart;
        BigDecimalInt floatPart;
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
};



#endif