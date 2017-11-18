/* 
 * File:   main.cpp
 * Author: GitHub@dobroalex
 *
 * Created on 18 ноября 2017 г., 13:20
 */
#define MY_VAR 7
#include "NumericalMethodsMath.h"
double f(double x);//несколько абстрактная ф-ция f(x) из  первой части второго задания. 
double Hn(double x, double a, double b , double pp, double pp1 );//ф-ла (3) из теории 
using namespace std;
double h; 
int main(int argc, char** argv) {
    double x[100], y[100], p1 = 1., p2 = -1.; //выбор точек
    int n = 1;
    h = 2./(double)(n);
    while (p1 != 1488 && p2 != 1488) {
        for (int j = -10000; j <= 10000; j++) {
            double x1 = 1.E-4 * (double)j;
            double y1 =Hn(x1, -1, 1, p1, p2);
            cout << "\nx1 = "<< x1 << "\ty1 = "<<y1 << "\tj = "<<j;
        }
        cin >> p1 >> p2;
    }
    cout <<"Endl";
    return 0;
}
double f(double x){ //несколько абстрактная ф-ция f(x) из  первой части второго задания. 
    return 1. / (1. + (5. + MY_VAR)*pow(x, 2.));
}
double Hn(double x, double a, double b, double pp, double pp1) { //ф-ла (3) из теории 
    double h1 = b -a ;
    double k = (x - a) / h1;
    return (1. - 3. * pow(k, 2.) + 2 *  pow(k, 3)) * f(a) + (3. * pow(k, 2)  - 2 * pow(k, 3.)) * f(b) + h* (k - 2. * pow(k, 2.) + pow(k, 3.)) * pp + h * (-pow(k, 2.) + pow(k, 3)) * pp1;
} 