/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab1.4.cpp
 * Author: DobroAlex 
 *
 * Created on 18 октября 2017 г., 20:20
 */


#include "NumericalMethodsMath.h"
using namespace std;

int main(int argc, char** argv) {
    cout << "i\tL[i]\tdx[i]\ti+dx[i]"<<endl;
    double P , a = 1.0E-7;
    double L[21], x[21];
    int i  = 1, j = 1;
    while (i <=20){
        P = 1.0;
        j = 1;
        while (j <=20){
            if (i != j) {
                P *= (double)(i- j );
            }
            j++;
        }
        L[i] = pow((double)i, 19.0) / P;
        x[i]     = L[i] * a;
        cout << i<<'\t' <<L[i]<<'\t' <<x[i]<<'\t'<<(double)i+x[i]<<endl;
        i++;
    }
    cout<<"L[i] показывает оценку изменения i-ого корня в зависимости от параметра (а-небольшая поправка к коэффициенту 19ой степени, равная 1E-7  . Очевидно, что для больших номеров корней, минимальная поправка сильно изменила корни " ;
    i = 0;
    return 0;
}

