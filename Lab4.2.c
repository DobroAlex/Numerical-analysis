

/* 
 * File:   Lab4.2.c
 * Author: GitHub@DobroAlex
 *
 * Created on 17 декабря 2017 г., 18:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "C_Plot.h"
double x[100], s1[100], s2[100], h[100], temp[100], y[] = {0.5, 0.8, 0.4, 0.8, 0.5};
double h1;
int n = 4;
void form1(double* a, double* b, double* c, double* f, double* x, double* y, double* h);
void form2(double* a, double* b, double* c, double* f, double* x, double* y, double* h);
void progonka1(double* x, double* y, double* h);
void progonka2(double* x, double* y, double* h);
double Si (double x [], double y [], double s [], double h [], int i, double xx);
int main(int argc, char** argv) {

    return 0;
}


void form1(double* a, double* b, double* c, double* f, double* x, double* y, double* h)
{
        a[0] = .0;
        b[0] = .0;
        c[0] = -1.;
        f[0] = .0;
        for (int i = 1;i < n; i++)
        {
            a[i] = h[i];
            b[i] = 2. * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6. * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
            ++i;
        }
        a[n] = 1.;
        b[n] = -1.;
        c[n] = .0;
        f[n] = .0;
}
void form2(double* a, double* b, double* c, double* f, double* x, double* y, double* h)
{
        a[1] = .0;
        b[1] = 2. * (h[1] + h[2]);
        c[1] = h[2];
        f[1] = 6. * ((y[2] - y[1]) / h[2] - (y[1] - y[0]) / h[1]);
        for (int i = 2; i < n - 1; i++)
        {
            a[i] = h[i];
            b[i] = 2. * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6. * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
        }
        a[n - 1] = h[n - 1];
        b[n - 1] = 2. * (h[n - 1] + h[n]);
        c[n - 1] = .0;
        f[n - 1] = 6. * ((y[n] - y[n - 1]) / h[n] - (y[n - 1] - y[n - 2]) / h[n - 1]);
}
void progonka1(double* x, double* y, double* h)
{
    double * a = (double *) malloc (100 * sizeof(double));
    double * b = (double *) malloc (100 * sizeof(double));
    double * c = (double *) malloc (100 * sizeof(double));
    double * f = (double *) malloc (100 * sizeof(double));
    double * p = (double *) malloc (100 * sizeof(double));
    double * q = (double *) malloc (100 * sizeof(double));
    form1(a, b, c, f, x, y, h);
    printf("\nProgonka1:\n");
    for (int i = 0; i <= n; i++)
    {
        printf("i = %d, a[%d] = %lf, b[%d] = %lf, c[%d] = %lf, f[%d]  = %lf\t", i , i , a[i], i, b[i], i, c[i], i, f[i]);
    }
    p[1] = (- c[0]) / b[0];
    q[1] = f[0] / b[0];
    for (int i = 1; i < n; i++)
    {
        double r = b[i] + a[i] * p[i];
        p[i + 1] = (- c[i]) / r;
        q[i + 1] = (f[i] - a[i] * q[i]) / r;
    }
     s1[n] = ((- a[n]) * q[n] + f[n]) / (b[n] + a[n] * p[n]);
     for (int i = n; i > 0; i--)
     {
         s1[i - 1] = p[i] * s1[i] + q[i];
     }
}
void progonka2(double* x, double* y, double* h)
{
        double * a = (double *) malloc (100 * sizeof(double));
        double * b = (double *) malloc (100 * sizeof(double));
        double * c = (double *) malloc (100 * sizeof(double));
        double * f = (double *) malloc (100 * sizeof(double));
        double * p = (double *) malloc (100 * sizeof(double));
        double * q = (double *) malloc (100 * sizeof(double));
        form2(a, b, c, f, x, y, h);
        printf("\nProgonka2:\n");
        for  (int i = 0;i <= n; i++) {
            
            printf("i = %d, a[%d] = %lf, b[%d] = %lf, c[%d] = %lf, f[%d]  = %lf\t", i , i , a[i], i, b[i], i, c[i], i, f[i]);
        }
        p[2] = (- c[1]) / b[1];
        q[2] = f[1] / b[1];
        
        for (int i  = 2;i < n - 1; i++) {
            double r = b[i] + a[i] * p[i];
            p[i + 1] = (- c[i]) / r;
            q[i + 1] = (f[i] - a[i] * q[i]) / r;
        }
        s2[n] = 0.0;
        s2[n - 1] = ((- a[n - 1]) * q[n - 1] + f[n - 1]) / (b[n - 1] + a[n - 1] * p[n - 1]);
        for  (int i = n - 1;i > 0; i--)
        {
            s2[i - 1] = p[i] * s2[i] + q[i];
            --i;
        }
        s2[0] = .0;
}
double Si (double x [], double y [], double s [], double h [], int i, double xx)
{
    return (s[i - 1] * pow(x[i] - xx, 3.0) + s[i] * pow(xx - x[i - 1], 3.0) + (xx - x[i - 1]) * (6.0 * y[i] - h[i] * h[i] * s[i]) + (x[i] - xx) * (6.0 * y[i - 1] - h[i] * h[i] * s[i - 1])) / (6.0 * h[i]);
}