/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab1.3.1.cpp
 * Author: DobroAlex
 *
 * Created on 16 октября 2017 г., 10:13
 */

#include "NumericalMethodsMath.h"

using namespace ::NumMet;
using std::cin;
using std::cout;
using std::endl;
using std::setprecision;

/*
 * 
 */
int main(int argc, char** argv) {
    double E[4][31];
    double a[4] = {0.0, 1E-5, 0.1, 1.0000};
    int m = 30, k = 0;
    for (int i = 0; i< 4; i++) {
        E[i][m] = a[i];
       // cout << E[i][m] << endl;  // debug porposes
    }
    cout << "k = "<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<' '<<endl;
    int i = 0;
    while (i < 4){
        m = 29;
        while (m >=1){
            E[i][m]  =  (1.0 -  E[i][m+1]) / (double)(m+1);
            m--;
        }
        i++;
    }
    m = 30;
    while ( m >=1){
        cout << "m= "<<m<<' ' <<" E0m= "<<E[0][m]<<' '<<" E1m = " << E[1][m]<<' '<<" E2m= "<<E[2][m]<<' '<<" E3m= "<<E[3][m]<<endl;
        k++;
        m--;
        
    }
    
    return 0;
}

