#include "NumericalMethodsMath.h"
using namespace std;
using ::NumMet::lagranz;
using ::NumMet::Newton;
int main(int argc, char** argv) {
    double OX[5] = {-1., -.5, .0 , .5,1.};
    double OY[5] ;
    /*Task 1 :::*/
    /*Берем случайных 5 точек на OX [-1;1] и 5 случайных на OY [0;1]*/
    NumMet::seed((long)time(NULL));
    for (int i = 0; i < 5; i++) { 
        cout << OX[i] <<"\t";
    }
    cout<<endl;
    for (int i = 0; i < 5; i++) { 
        OY[i] = OX[i]*OX[i]; //например берем экспоненту x^2
        cout << OY[i] <<"\t";
    }
    cout << endl;
    /*У нас есть N точeк, степень полинома не больше, чем N-1*/
    for (int i = 0; i < 5 ; i++) {
        cout << "X=" << OX[i] << "\tF(x) = "<<OY[i]<<"\tLn(x) = "<<lagranz(OX[i], OX, OY, 5 )<<"\tNewton(x)="<<Newton(OX[i], 5, OX, OY, OX[1]-OX[0])<<endl;
    }
    getchar();
    int n[2] = {10,20};
    cout<<"\n\n\n A:f(x) = |x|\n\n\n";
    getchar();
    for (int j = 0; j < 2; j++) {
        double  * X = new double [n[j]+1];
        double  * realF = new double [n[j]+1];
        for (int i = 0; i <= n[j]; i++) {
            double h = 2./n[j];
            X[i] = -1. + i * h;
            realF[i] = NumMet::abs(X[i]);
        }
        cout << "Интерполяция:";
        for (int  i = 0; i <= n[j]; i++) {
            cout<<"\nn = " << n[j] << "\ti = " << i << "\tX = "<<X[i]<<"\tF(x) = " << realF[i]<<"\tLn(x) = " << NumMet::lagranz(X[i], X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(X[i], n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        cout <<"\nЭкстарполяция:\n";
        for (double test = -1./(X[1]-X[0]); test <= 1./(X[1]-X[0]); test += (X[1]-X[0]) ) {
            cout << "\nn = " << n[j] << "\tx= " << test << "\tF(x) = " <<  NumMet::abs(test) <<"\tLn(x) = " << NumMet::lagranz(test, X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(test, n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        delete [] X;
        delete [] realF;
    }
    cout << "\n\n\nB:f(x) = x^3";
    getchar();
    for (int j = 0; j < 2; j++) {
        double  * X = new double [n[j]+1];
        double  * realF = new double [n[j]+1];
        for (int i = 0; i <= n[j]; i++) {
            double h = 2./n[j];
            X[i] = -1. + i * h;
            realF[i] = pow(X[i], 3.);
        }
        cout << "Интерполяция:";
        for (int  i = 0; i <= n[j]; i++) {
            cout<<"\nn = " << n[j] << "\ti = " << i << "\tX = "<<X[i]<<"\tF(x) = " << realF[i]<<"\tLn(x) = " << NumMet::lagranz(X[i], X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(X[i], n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        cout <<"\nЭкстарполяция:\n";
        for (double test = -1./(X[1]-X[0]); test <= 1./(X[1]-X[0]); test += (X[1]-X[0]) ) {
            cout << "\nn = " << n[j] << "\tx= " << test << "\tF(x) = " <<  NumMet::abs(test) <<"\tLn(x) = " << NumMet::lagranz(test, X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(test, n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        delete [] X;
        delete [] realF;
    }
    cout << "\n\n\nC:f(x) = cos(PI*x/2)";
    getchar();
    for (int j = 0; j < 2; j++) {
        double  * X = new double [n[j]+1];
        double  * realF = new double [n[j]+1];
        for (int i = 0; i <= n[j]; i++) {
            double h = 2./n[j];
            X[i] = -1. + i * h;
            realF[i] = cos(MY_PI*X[i]/2.);
        }
        cout << "Интерполяция:";
        for (int  i = 0; i <= n[j]; i++) {
            cout<<"\nn = " << n[j] << "\ti = " << i << "\tX = "<<X[i]<<"\tF(x) = " << realF[i]<<"\tLn(x) = " << NumMet::lagranz(X[i], X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(X[i], n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        cout <<"\nЭкстарполяция:\n";
        for (double test = -1./(X[1]-X[0]); test <= 1./(X[1]-X[0]); test += (X[1]-X[0]) ) {
            cout << "\nn = " << n[j] << "\tx= " << test << "\tF(x) = " <<  NumMet::abs(test) <<"\tLn(x) = " << NumMet::lagranz(test, X, realF, n[j]+1) << "\tNn(x) = " << NumMet::Newton(test, n[j]+1, X, realF, X[1]-X[0])<<endl; 
        }
        delete [] X;
        delete [] realF;
    }
    return 0;
}

