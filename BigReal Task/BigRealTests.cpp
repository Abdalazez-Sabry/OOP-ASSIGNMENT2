#include <iostream>
#include <random>
#include <iomanip>
#include "BigReal.h"

using namespace std;


vector<double> randomDoubles(int range){
    vector<double> result;
    for (int i = 0; i < range; i++){
        string negation =(rand() % 2 == 0)? "" : "-";
        double randomDouble = stod(negation + to_string(rand()) + "." + to_string(rand()));
        result.push_back(randomDouble);
    }
    return result;
}

// test the + and - operations on BigReal and compare the result with c++ double
void test1(){
    vector<double> randDs = randomDoubles(200);
    for (int i = 0; i < randDs.size(); i += 2){
        BigReal big1(randDs[i]), big2(randDs[i + 1]);
        bool pass = ((big1 + big2) == BigReal(randDs[i] + randDs[i + 1]));
        
        if (!pass){
            cout << "\n\t\t---TEST1 FAIL---\n" << endl;
            cout << "big " << big1.getNumber() << " + " << big2.getNumber() << " = " << (big1 + big2).getNumber() << endl;
            cout << setprecision(10) << "double " << randDs[i] << " + " << randDs[i + 1] << " = " << randDs[i]  + randDs[i + 1] << endl;
            return;
        }
    }
    cout << "test1 pass" << endl;
}
// test the <, > and == operations on BigReal and compare the result with c++ double 
void test2(){
    vector<double> randDs = randomDoubles(200);
    for (int i = 0; i < randDs.size(); i += 2){
        BigReal big1(randDs[i]), big2(randDs[i + 1]);
        bool pass = ((big1 > big2) == (randDs[i] > randDs[i + 1]));
        if (!pass){
            cout << "\n\t\t---TEST2 FAIL---\n" << endl;
            cout << "big " << big1.getNumber() << " > " << big2.getNumber() << " = " << (big1 > big2)<< endl;
            cout << setprecision(10) << "double " << randDs[i] << " > " << randDs[i + 1] << " = " << (randDs[i]  > randDs[i + 1]) << endl;
            return;
        }
        pass = ((big1 < big2) == (randDs[i] < randDs[i + 1]));
        if (!pass){
            cout << "\n\t\t---TEST2 FAIL---\n" << endl;
            cout << "big " << big1.getNumber() << " < " << big2.getNumber() << " = " << (big1 < big2)<< endl;
            cout << setprecision(10) << "double " << randDs[i] << " < " << randDs[i + 1] << " = " << (randDs[i]  < randDs[i + 1]) << endl;
            return;
        }
        pass = ((big1 == big2) == (randDs[i] == randDs[i + 1]));
        if (!pass){
            cout << "\n\t\t---TEST2 FAIL---\n" << endl;
            cout << "big " << big1.getNumber() << " == " << big2.getNumber() << " = " << (big1 > big2)<< endl;
            cout << setprecision(10) << "double " << randDs[i] << " == " << randDs[i + 1] << " = " << (randDs[i]  == randDs[i + 1]) << endl;
            return;
        }
    }
    cout << "test2 pass" << endl;
}
// test zeros initializations
void test3(){
   for (int i = 0; i < 20; i++){ 
        string beforePoint(i + 1, '0'), afterPoint(i + 1, '0'), point(".");
        BigReal bg(beforePoint + point + afterPoint);
        BigReal nbg("-" + beforePoint + point + afterPoint);
        bool pass = (bg.getNumber() == "0") && (nbg.getNumber() == "0");
        if (!pass){
            cout << "\n\t\t---TEST2 FAIL---\n" << endl;
            cout << bg.getNumber() << " /= " << "0" << endl;
            cout << nbg.getNumber() << " /= "  << "0"<< endl;
            return;
        }
   }
    cout << "test3 pass" << endl;
}
// test with specific numbers
void test4(){
    vector<double> numsToCheck{0, 1, 2, -0. -1, -2, 0.1, 0.2, -0.1, -0.2, 0.00003, 0.0000000007, 0.0000000032, 0.08320003,
    -0.00000000032, -0.832673032, 23738485, -384957696 
    };
    for (double num1 : numsToCheck){
        for (double num2 : numsToCheck){
            string bigRealResult = (BigReal(num1) + BigReal(num2)).getNumber();
            double doubleResult = num1 + num2;
            bool pass = (abs(stod(bigRealResult)  - doubleResult ) < 0.0001) ;
            if (!pass){
                cout << "\n\t\tTEST4 FAIL" << endl;
                cout << num1  << " + " << num2 << " = " << bigRealResult <<  endl; 
                return;
            }
        }
    }
    cout << "test4 pass" << endl;
}
int main(){
    BigDecimalInt c("-123");
    BigReal a, b("123.2"), d(c), e(a);
    cout << a << "__" << b << "__" << d << e << endl;
    a = d;
    d = (b - d);
    e = (a + b);
    cout << a << "__" << b << "__" << d << e << endl;
    cout << (a < d) << "__" << (b > e) << "__" << (d == a) << endl;
    cout << b.size() << "__" << d.sign() << "__" << d << endl;
    cin >> a >> b >> d >> e;
    cout << a << "__" << b << "__" << d << e << endl;
    test1();
    test2();
    test3();
    test4();

    // BigReal x("-0750.000");
    // BigReal y("-500.5");
    // BigReal z ("500.5");
    // BigReal t("-500.5");
    // BigReal n("0");
    // // cout << n.getNumber() << endl;
    // // cout << (t+n).getNumber() << endl;

    // // cout << x.getNumber() << y.getNumber() << endl;
    // // cout << (x>y) << " second " << (y<z) << " third "<< (z>t) << " fourth " << (n>x) << " fifth " << (n > z) << endl;
    // // cout << x.getNumber() << y.getNumber() << endl;
    // // cout << x.getNumber() << y.getNumber() << endl;
    // // cout << (x>y) << " second " << (y<z) << " third "<< (z>t) << " fourth " << (n>x) << " fifth " << (n > z) << endl;
    // // cout << x.getNumber() << y.getNumber() << endl;

    // // cout << y.getNumber() << " second " << x.getNumber() << endl;

    // // cout << x.getNumber() << endl;
    // // z = x - y;
    // // cout << z.getNumber() << endl << " y: " << x.getNumber();
    // // cout << x.getNumber() << endl;
    // z = x-x;
    // cout << z.getNumber() << endl;
    
 
}