/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab1.3.cpp
 * Author: DobroAlex
 *
 * Created on 14 октября 2017 г., 15:56
 */

#include "NumericalMethodsMath.h"
using namespace NumMet;
using std::cin;
using std::cout;
using std::endl;
using std::pow;
using std::setprecision;
/*
 * 
 */
double E[4][21];
double eps[4] = { 0.0, 1.0E-7, 1.0E-6, 1.0E-5 };
int main(){
    int k = 0;
    int i = 0;
    while (i < 4) {
        k = 1;
        E[i][k] = MY_REV_E + eps[i];
        k = 2;
        while ( k <= 20){
            E[i][k] = 1.0 -  (double)k * E[i][k-1];
            ++k;
        }
        ++i;
    }
    i = 0;
    while ( i < 4){
        k = 1;
        while (k <= 20) {
            cout<<"k= "<<k<<" i= "<<i<<" E= "<<setprecision(30)<<E[i][k]<<endl;
            ++k;
        }
    ++i;
    }
    return 0;
}

