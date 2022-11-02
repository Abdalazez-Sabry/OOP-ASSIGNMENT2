#include <iostream>
#include <random>
#include <iomanip>
#include "BigReal.cpp"

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
    test1();
    test2();
    test3();
    test4();


    
 
}