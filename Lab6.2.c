
/* 
 * File:   Lab6.2.c
 * Author: DobroAlex
 *
 * Created on 17 декабря 2017 г., 21:12
 */

const double newCoef [] [100] = { //коэф-ты Ньютона  https://code-live.ru/post/cpp-array-tutorial-part-2/
    {.5 , .5},
    {.166, 0.666, .166},
    { .125, .375, .375, .125},
    { .065, .26, .173, .173, .26, .065}
};
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <float.h>
//#define DEBUG
double trapeze (double a, double b, int n); //интеграл методом тарпеций на отрезке [a;b] с разбиением на n отрезков. Т.к разбиение равномерное, то это метод Котеса
double newtonCot (double a, double b, int n); //Ньютон-Котес на отрезке [a;b] с разбиенями n 
double testFunc (double x) ; //ф-ция с котрой работаем 
int main(int argc, char** argv) {
#ifdef DEBUG
    printf ("Trapeze :n = 5 = %lf", trapeze (2,5,5) );
#endif
    for(int n = 0; n <=3; n++)
    {
        printf ("\n Trapeze (0, PI/2,%d) = %lf, N-C (0,PI/2,%d) = %lf", n, trapeze(0,M_PI,n), n, newtonCot(0,M_PI,n));
    }
    return (0);
}
double testFunc (double x)  //ф-ция с котрой работаем 
{
#ifdef DEBUG
    return 1./log(x); //на этой ф-ции отлаживался метод трапеций 
#endif
    return cos(x)/(1.+x); //а это по заданию

}
double newtonCot (double a, double b, int n) //Ньютон-Котес на отрезке [a;b] с разбиенями n
{
    double h = (b-a)/n;
    double *x = (double*) malloc ((n+1) * sizeof(double)), *y = (double*) malloc ((n+1) * sizeof(double));
    x[0] = a;
    y[0] = testFunc(a);
    for (int i = 1; i <=n; i++)
    {
        x[i] = x[i-1] +h;
    }
    for (int i = 1; i <= n; i++)
    {
        y[i] = testFunc (x[i]);
    }
    double range = b-a; //(b-a)
    double sum = .0;
    for (int i = 0; i < n; i++)
    {
        sum += newCoef[n-1][i] * y[i];
    }
    return range*sum;
}
double trapeze (double a, double b, int n) //интеграл методом тарпеций на отрезке [a;b] с разбиением на n отрезков. Т.к разбиение равномерное, то это метод Котеса
{
    double h =  (b-a)/(double)n;
    double * x0 = (double *) malloc ((n+1) * sizeof(double)), *y0 = (double *) malloc ((n+1) * sizeof(double));
    x0[0] = a;
    y0[0] = testFunc(x0[0]);
    for (int i = 1; i<=n; i++)
    {
        x0[i] = x0[i-1]+h;
        y0[i] = testFunc(x0[i]);
    }
    double sum = .0;
    for (int i = 1; i < n; i++)
    {
        sum += y0[i];
    }
#ifdef DEBUG
    printf ("\n_______Trapeze Method\n_______");
    printf ("\nh = %lf\n", h);
    for (int i = 0; i <= n; i++)
    {
        printf ("X[%d] = %lf, f(X[%d]) = %lf\t", i, x0[i],  i , y0[i]);
    }
    printf ("\n  h * ((y0[0]+y0[n])/2. + sum) === %lf * ((%lf+%lf)/2. + %lf) \n\n\n", h, y0[0], y0[n], sum);
#endif
    /*Не почистил malloc == утекло*/
    return h * ((y0[0]+y0[n])/2. + sum);
    
}
