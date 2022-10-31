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
        void removeFloatZeros();
        void suffixZeros(BigDecimalInt & first, BigDecimalInt & second);
    
    public:
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

void BigReal::sperateIntAndFloat(string num){
    int decimalPointPos = num.find(".");

    if (decimalPointPos == -1){
        intPart = BigDecimalInt(num);
        floatPart = BigDecimalInt("0");
    }else{
        intPart = num.substr(0, decimalPointPos);
        floatPart = num.substr(decimalPointPos + 1);
        removeFloatZeros();
    }

}
void BigReal::removeFloatZeros(){
    string f = floatPart.getNumber(); 
    for (int i = f.size() - 1; i > 0; i --){
        if (f[i] == '0'){
            f.erase(i, 1);
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
    string resultStr = "";
    BigDecimalInt resultIntPart, resultFloatPart;

    suffixZeros(floatPart, anotherReal.floatPart);

    resultIntPart = intPart + anotherReal.intPart;
    resultFloatPart = floatPart + anotherReal.floatPart;

    resultStr = resultIntPart.getNumber() + "." + resultFloatPart.getNumber();
    char sign = (resultIntPart.sign() == 1) ? '+' : '-';
    return BigReal(sign + resultStr);
}

void BigReal::suffixZeros(BigDecimalInt & first, BigDecimalInt & second){
    
    // string& noChange = (first.getNumber().length() > second.getNumber().length())? first.getNumber() : second.getNumber();
    // string& toAddZeros = (first.getNumber().length() > second.getNumber().length())? second.getNumber() : first.getNumber();

    // int difference = noChange.length() - toAddZeros.length();
    // string suffix (difference, '0');
    // string temp = toAddZeros + suffix;
    // toAddZeros = temp;
}
int main(){
    BigReal x("2.4");
    BigReal y("1.56");
    BigReal z = x + y;
    BigDecimalInt d("-32");
    cout << z.getNumber() << endl;

}