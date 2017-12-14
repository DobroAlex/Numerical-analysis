/* 
 * File:   Lab6.1.c
 * Author: DobroAlex
 *
 * Created on 13 декабря 2017 г., 18:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <stdbool.h>
#include <float.h>
#define DEBUG 
/*Нужен для отладочных целей, при этом интеграл считается от 1/x на [1,2].
 Чтоб убрать связанный вывод и запустить основную функцию вычсиления, закомментируйте строку #define DEBUG */
bool isEqual(double a, double b); //проверяет два double на равенство через машинный эпсилон
double testFunc(double x); //интегрируемая функция
double integrSimpson (double epsilon, double a, double b,double h); //интеграл Симпосна на отрезке a,b, с точностью epsilon. Интегрируемая функция -- double testFunc(x)
int main(int argc, char** argv) {
#ifdef DEBUG
    printf("\n\n\t\t%lf",integrSimpson(.01, 1, 2, .5));
#endif
#ifndef DEBUG
    printf("\n\n\t\t%lf",integrSimpson(.01, 0, 1, .5));
#endif
    return 0;
}
double testFunc(double x)//интегрируемая функция
{
#ifdef DEBUG
    return 1./x;
#endif
#ifndef DEBUG
    return (cosh(x)-1.)/x;
#endif
}
double integrSimpson (double epsilon, double a, double b, double h) //интеграл Симпосна на отрезке a,b, с точностью epsilon. Интегрируемая функция -- double testFunc(x)
{
    const int A = 180; //знаменатель из формулы оценки погрешности
    const int p = 4; // порядок апроксимации
    double S2, S1; //для формулы Рунге
    int n = (b-a)/h;
#ifdef DEBUG
    printf("\nn=%d\n\n",n);
#endif
    double  * x0 =  (double *) malloc( (n+1) * sizeof(double)), *f0 = (double*) malloc((n+1) * sizeof(double));//явный каст для собирающих g++
    double sumOfOdd= .0;
    double sumOfEven = .0;
    //double step = fabs(a-b)/n;
    for (int  i = 0; i <=n; i++)
    {
        x0[i] = a+i*h;
        f0[i] = testFunc(x0[i]);
#ifdef DEBUG
        printf ("X0[%d] = %f , F0[%d] =  %f\t", i, x0[i], i, f0[i]);
#endif
    
    }
    for (int i = 1; i < n; i++)
    {
        if ( i % 2 == 0)
        {
            sumOfEven += f0[i];
        }
    }
#ifdef DEBUG
    printf("\n sumOfEven =  %lf\n", sumOfEven);
#endif 
    for (int  i = 1; i <=n ; i++)
    {
        if ( i % 2 != 0)
        {
            sumOfOdd += f0[i];
        }
    }
#ifdef DEBUG  
    printf("\n sumOfOdd =  %lf\n", sumOfOdd);
#endif 
#ifdef DEBUG
    //printf ("h/3 = %lf , f0 = %lf, 4*Odd + ")
#endif
    return (h/3.) * (testFunc(x0[0]) + 4 * sumOfOdd + 2 * sumOfEven + testFunc(x0[n]));
}
bool isEqual(double a, double b) //проверяет два double на равенство через машинный эпсилон
{
    if (fabs(a-b) <= DBL_EPSILON)
    {
        return true;
    }
    return false;
}