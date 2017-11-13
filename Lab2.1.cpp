#include "NumericalMethodsMath.h"
#define MY_VAR 7 /*Мой вариант*/
using namespace std;
using NumMet::lagranz;
using NumMet::lenBetweenpoints;
/*int lenBetweenpoints (int x1, int x2);
double lagranz(double t, double * X, double *Y, double n  ); //интерполяционный многочлен */
double testFunc(double x); /*Функция, которую интерполируем */
int main(int argc, char** argv) {
    /*Interpolation corectness test*/
    double OX[5] = {-1.0, -.5, .0, .5, 1.0};
    double OY[5];
    for (int i = 0; i < 5; i++ ) {
        OY[i] = testFunc(OX[i]); //заполняем полиномом четвертой степени  
    }
    cout << "OX = ";
    for (int i = 0; i < 5; i++) {
        cout <<OX[i]<<"   ;   ";
    }
    cout << "\nOY = ";
    for (int i = 0; i < 5; i++) {
        cout <<OY[i]<<"   ;   ";
    }
    cout << endl;
    for (double test = .0; test <10; test+= 1.0){
        cout << "test val = " << test <<"; F(x) = " << testFunc(test)<< "; Ln(x) = " << lagranz(test, OX, OY, 5)<<endl;
        //как видим интерполяция точна  
    }
    getchar();
    
    /*Task 1 :::*/
    /*Берем случайных 5 точек на OX [-1;1] и 5 случайных на OY [0;1]*/
    NumMet::seed((long)time(NULL));
    for (int i = 0; i < 5; i++) { 
        OX[i] = NumMet::rnd();
        cout << OX[i] <<"\t";
    }
    cout<<endl;
    for (int i = 0; i < 5; i++) { 
        OY[i] = OX[i] * OX[i]; //меняем на какую-то конкретную ф-цию, х^2
        cout << OY[i] <<"\t";
    }
    cout<<"\n Значение в узлах :\n";
    for ( int i = 0; i < 5; i++){
        cout <<"X = " << OX[i] << "\tF(x)= "<<OY[i]<<"\tLn(x) = "<<lagranz(OX[i], OX, OY, 5)<<endl;
    }
    cout << endl;
    
    /*Task 2 ::: */
    /*f(x) = 1/(1+d*x^2), x [-1;1], d = 10+k;*/
    /*Part (a)*/
    int n[] = {4, 10, 20};
    cout <<"\n\n\nРавномерное разбиение\n\n\n";
    for (int j = 0; j < (int)(sizeof(n)/sizeof(n[0])); j++) {
        double  * realF = new double [n[j]];
        double * X = new double [n[j]];
        for (int i = 0; i < n[j];i++) {
            double h = 2./n[j];
            X[i] = -1. + i *h;
            realF[i] = 1./(1. + (10 + MY_VAR)* pow(X[i], 2.));
        }
        for (int  i = 0; i < n[j]; i++) {
            cout <<"\n n = " << n[j] <<"\t i = " << i << "\t X=" << X[i] << "\t F(x) = " << realF[i] << "\t Ln(x) =" << lagranz(X[i], X, realF, n[j]);
        }
        cout << "\n\n\n";
       delete [] X;
       delete [] realF;
    }
    /*Чебышев*/
    cout<<"\n\n\n Чебышев \n\n\n";
    for (int j = 0; j < 3; j++) {
        double *realF = new double [n[j]+1];
        double * X = new double [n[j]+1];
        for (int i = 0; i <= n[j]; i++) {
            double N = 2*(n[j]+1);
            X[i] = cos((2.0*(double)i + 1.0) * M_PI / N);
            realF[i] = 1./(1.+ (10. + MY_VAR)*X[i]*X[i]);
        }
        for (int i = 0; i<=n[j];i ++) {
            cout << "\n n=" << n[j] <<"\t i = " << i<<"\t X =" << X[i] << "\t F(x) = " << realF[i] << "\t Ln(x) = " << NumMet::lagranz(X[i], X, realF, n[j])<<endl;
        }
    }
    return 0;
}



inline double testFunc(double x) {
	return  2. * x*x*x*x + 3. * x*x*x + 4.*x*x + x + 5.; // for example
}