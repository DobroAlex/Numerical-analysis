/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab2.1.cpp
 * Author: DobroAlex 
 *
 * Created on 25 октября 2017 г., 13:04
 */

#include "NumericalMethodsMath.h"
#define MY_VAR 7 /*Мой вариант*/
using namespace std;
using NumMet::lagranz;
using NumMet::lenBetweenpoints;
/*int lenBetweenpoints (int x1, int x2);
double lagranz(double t, double * X, double *Y, double n  ); //интерполяционный многочлен */
double testFunc(double x); /*Функция, которую интерполируем */
double Chebyshev (int n , double t ) ; //многочлен Чебышева n-ого рода,  -1<=t<=1
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
        cout << "test val = " << test << "; Ln(x) = " << lagranz(test, OX, OY, 5)<<"; F(x) = " << testFunc(test)<<endl;
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
        OY[i] = NumMet::rnd();
        cout << OY[i] <<"\t";
    }
    cout << endl;
    /*У нас есть N точeк, степень полинома не больше, чем N-1*/
    for (double test = -5.0; test  <= 5.0; test += 1.0) {
        cout << " Test value = " << test << " F = " << lagranz(test, OX, OY, 5)<<endl;
    }
    getchar();
    
    /*Task 2 ::: */
    /*f(x) = 1/(1+d*x^2), x [-1;1], d = 10+k;*/
    /*Part (a)*/
    int n[] = {4, 10, 20};
    for (int j = 0; j < (int)(sizeof(n)/sizeof(n[0])); j++) {
        double  * realF = new double [n[j]];
        double * X = new double [n[j]];
        double ansX = -1.;
        double len = ::lenBetweenpoints(-1,1);
        double delta  = (double)::lenBetweenpoints(-1, 1) / (double)(n[j]);
        X[0] = -1.;
        for (int i = 1 ; i < n[j]; i++) {
            X[i] = X[i-1] + delta;    
            double h = 2.0 / n[j];
        //cout<<endl<<endl;
            realF[i] = 1.0/(1.0 + (10+MY_VAR)* X[i] * X[i]);
            cout<<"n = " <<n[j] << " i = " << i <<" X[i] = " << X[i] << " realF[i] = " << realF[i] << endl;
        }
        cout<<"Into/Extropolation:\n";
        for (double test = -2.;test <= 2.; test+=delta ){
            cout<<"X = "<<test<<"\tReal F(x) = " <<  1.0/(1.0 + (10+MY_VAR)* test * test) << "\tLn(x) = "<<::lagranz(test, X, realF, n[j])<<endl;
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
            cout << "\n n=" << n[j] <<"\t X =" << X[i] << "\t F(x) = " << realF[i] << "\t Ln(x) = " << NumMet::lagranz(X[i], X, realF, n[j])<<endl;
        }
    }
    return 0;
}



inline double testFunc(double x) {
	return  2.0 * x*x*x*x + 3.0 * x*x*x + 4.0*x*x + x + 5.0; // for example
}
inline double Chebyshev (int n , double t ) { //многочлен Чебышева n-ого рода,  -1<=t<=1
    return cos ( (double)n * acos(t)); //http://www.intuit.ru/studies/courses/1012/168/lecture/4600?page=5
}