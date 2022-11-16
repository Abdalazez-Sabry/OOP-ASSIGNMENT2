#include <iostream>
#include <functional>

using namespace std;


class Function{
    public : virtual double evaluateAt(double value) = 0;
};

class SimpleFunction : public Function{
    private: function<double(double)> f;

    public:
        SimpleFunction(function<double(double)> f){
            this->f = f;
        }
        double evaluateAt(double value){
            return f(value);
        }
};

class CompositionFunction : public Function{
    private:
        function<double(double)> f1;
        function<double(double)> f2;

    public:
        CompositionFunction(function<double(double)> f1, function<double(double)> f2){
            this->f1 =f1;
            this->f2 =f2;
        }
        double evaluateAt(double value){
            return f1(f2(value));
        }
};

class DerivativeFunction : public Function{
    private:
        function<double(double)> f;
        double deltaX;
    public:
        DerivativeFunction(function<double(double)>f , double deltaX){
            this->f = f;
            this-> deltaX = deltaX;
        }
        double evaluateAt(double x){
            return (f(x + deltaX) - f(x - deltaX)) / (2 * deltaX);
        }
};

double cube (double n) {
    return n * n * n;
}

double second (double d) {
    return d * d - 5 * d - 4;
}

double fun (double d) {
    return d * d - 3 * d - 4;
}

int main(){
    SimpleFunction f1([](double n) ->double {return n * n;});
    cout << f1.evaluateAt(5) << endl;

    DerivativeFunction f2 (second, 5);
    cout << f2.evaluateAt(5) << endl;

    CompositionFunction f3 (fun, cube);
    cout << f3.evaluateAt(5) << endl;

    return 0;
}