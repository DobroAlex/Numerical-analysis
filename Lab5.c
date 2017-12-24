
/* 
 * File:   Lab5.c
 * Author: DobroAlex
 *
 * Created on 24 декабря 2017 г., 20:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "C_Plot.h"
#define MINX .0
#define MINY .0
#define MAXX 12.
#define MAXY 6.
#define MY_VAR 7
double A[100][100],  a[100],  b[100], c[100][100], x[]  = {1.0, 2.0, 3.0, 4.0, 5.0}, y[]= {1.0, 2.0, 1.0, 3.0, 2.0}, B = 0.0, C = 0.0, D = 0.0, E = 0.0, a1, b1,s1, s2, s3;
int N = 5, n1 = 1, n2 = 2;
double f1(double x, int n);
double f2(double x, int n);
double f3(double x);
void form(double x[], double y[], int n);
void nelin(double x[] , double y[] );
void copy(int n);
void pere(int i, int j, int n);
void max(double a[100][100] , int i, int n);
void gauss1(double x[] , double y[] , int n);
void gauss2(double x[], double y[],  int n);
int main(int argc, char** argv) {
            plPlotter *plotter;
            plPlotterParams *plotter_params;

           /* set a Plotter parameter */
           plotter_params = pl_newplparams ();
           pl_setplparam (plotter_params, "PAGESIZE", "letter");

           /* create a Postscript Plotter that writes to standard output */
           if ((plotter = pl_newpl_r ("X", stdin, stdout, stderr,
                                      plotter_params)) == NULL)
             {
               fprintf (stderr, "Couldn't create Plotter\n");
               return 1;
             }

            if (pl_openpl_r (plotter) < 0)      /* open Plotter */
             {
               fprintf (stderr, "Couldn't open Plotter\n");
               return 1;
             }
          
           pl_fspace_r (plotter, MINX, MINY, MAXX, MAXY); /* set coor system */

            pl_flinewidth_r (plotter, 0.25);    /* set line thickness */
            pl_pencolorname_r (plotter, "red"); /* use red pen */
            pl_erase_r (plotter);               /* erase graphics display */
           //pl_fmove_r (plotter, 600.0, 300.0); /* position the graphics cursor */
            pl_endpath_r(plotter);
            drawAxises(plotter, MINX, MINY, MAXX, MAXY, 0.01, "black");
            drawSegsX(plotter, MINX, MAXX, fabs(MAXY-MINY)/2., fabs((MAXX-MINX)/(MAXX-MINX)), .5, "black");
            drawSegsY(plotter, MINY, MAXY, fabs(MAXX-MINX)/2.,  fabs((MAXY-MINY)/(MAXY-MINY)), .5, "black");
            pl_endpath_r(plotter);
            pl_pencolorname_r (plotter, "black"); /* use black pen */
            for (int i = 0; i < N; i++)
            {
                pl_fmarker_r(plotter, x[i]+fabs(MAXX-MINX)/2.,y[i]+fabs(MAXY-MINY)/2.,15,.5);
                //printf("%lf %lf\n", x[i]+fabs(MAXX-MINX)/2.,y[i]+fabs(MAXY-MINY)/2.);
            }
            gauss1(x, y, n1);
            gauss2(x, y, n2);
            nelin(x, y);

            pl_pencolorname_r (plotter, "blue");
            printf ("\nТаблица точек линейной функции:\n");
            for (int i = 0; i < N;i++)
            {
                pl_fmarker_r(plotter, x[i]+fabs(MAXX-MINX)/2., f1(x[i],n1)+fabs(MAXY-MINY)/2., 31, .5/2.);
                printf (" (%lf;%lf)   ", x[i], f1(x[i],n1) );
            }
            pl_pencolorname_r (plotter, "red");
            printf ("\nТаблица точек квадратичной функции:\n");
            for (int i = 0; i < N;i++)
            {
                pl_fmarker_r(plotter, x[i]+fabs(MAXX-MINX)/2., f2(x[i],n2)+fabs(MAXY-MINY)/2., 31, .5/2.);
                printf (" (%lf;%lf)   ", x[i], f2(x[i],n2) );
            }
            pl_pencolorname_r (plotter, "green");
            printf ("\nТаблица точек степенной функции:\n");
            for (int i = 0; i < N;i++)
            {
                pl_fmarker_r(plotter, x[i]+fabs(MAXX-MINX)/2., f3(x[i])+fabs(MAXY-MINY)/2., 31, .5/2.);
                printf (" (%lf;%lf)   ", x[i], f3(x[i]) );
            }
            
            
            
                if (pl_closepl_r (plotter) < 0)     /* close Plotter */
      {
        fprintf (stderr, "Couldn't close Plotter\n");
        return 1;
      }
     
    if (pl_deletepl_r (plotter) < 0)    /* delete Plotter */
      {
        fprintf (stderr, "Couldn't delete Plotter\n");
        return 1;
      }
    return 0;
}
double f1(double x, int n) {
        double s = 0.0;
        int i = 0;
        while (i <= n) {
            s += a[i] * pow(x, i);
            ++i;
        }
        return s;
    }
double f2(double x, int n) 
{
        double s = .0;
        for(int i = 0;i <= n; i++)
        {
            s += b[i] * pow(x, i);
        }
        return s;
}
double f3(double x)
{
        return a1 * pow(x, b1);
}
void form(double x[], double y[], int n)
{
    double sumX[100], sumY[100];
    sumX[0] = N;
    for (int  i = 1; i <= 2 * n; i++)
    {
        sumX[i] = .0;
        for (int j = 0; j  < N; j++)
        {
            double* arrd = sumX;
            int n2 = i;
            arrd[n2] +=     pow(x[j], i);
        }
    }
    for (int i = 0; i <= n ; i++)
    {
        sumY[i] = .0;
        for (int j = 0; j< N; j++)
        {
            double* arrd = sumY;
            
            int n3 = i;
            arrd[n3] += pow(x[j],i) * y[j];
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            A[i][j] = sumX[i+j];
            A[i][j+1] = sumY[i];
        }
    }
}
void nelin(double x[] , double y[] )
{
    for(int i = 0; i < N; i++)
    {
      B += log10(x[i]);
      C += log10(y[i]);
      D += pow(log10(x[i]), 2.);
      E += log10(x[i]) * log10(y[i]);
    }
    b1 = (B * C - (double)N * E) / (B * B - (double)N * D);
    a1 = exp((C - B * b1) / (double)N);
}
void copy(int n)
{
    for (int  i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n+1; j++)
        {
            c[i][j] = A[i][j];
        }
    }
}
void pere(int i, int j, int n) 
{
        double temp[100];
        for(int k = 0;k <= n + 1; k++)
        {
            temp[k] = c[j][k];
            c[j][k] = c[i][k];
            c[i][k] = temp[k];
        }
}
void max(double a[100][100] , int i, int n)
{
    int l = i;
    for (int k = i; k < n; k++)
    {
        if(fabs(a[l][i])<fabs(a[k][i]))
        {
            l = k;
        }
    }
    if (l != i)
    {
        pere(i,l,n);
    }
}
void gauss1(double x[] , double y[] , int n)
{
    form(x,y,n);
    copy(n);
    for (int i = 0; i <= n; i++)
    {
        max(c,i,n);
        if (fabs(c[i][i] - .0) < DBL_EPSILON) // if (c[i][i] == 0.0)
        {
            break;
        }
        for (int j = i + 1; j <=n; j++)
        {
            double m = c[i][j]/c[i][i];
            for (int k =  i; k <= n+1;k++)
            {
                c[j][k] = c[j][k] - m * c[i][k];
            }
        }
    }
    a[n] = c[n][n + 1] / c[n][n];
    for (int i = n-1; i >= 0; i--)
    {
        double sum = c[i][n+1];
        for(int k = i + 1; k <= n; k++)
        {
            sum -= c[i][k] * a[k];
        }
        a[i] = sum / c[i][i];
    }
}
void gauss2(double x[], double y[] , int n) {
        form(x, y, n);
        copy(n);
        for(int i = 0;i <= n;i++)
        {
            max(c, i, n);
            if (fabs(c[i][i]- .0) < DBL_EPSILON)//if (this.c[i][i] == 0.0) break;
            {
                break;
            }
            for(int j = i + 1;j <= n;j++)
            {
                double m = c[j][i] / c[i][i];
                for (int k = i;k <= n + 1; k++)
                {
                    c[j][k] = c[j][k] - m * c[i][k];

                }

            }

        }
        b[n] = c[n][n + 1] / c[n][n];
        for ( int i = n - 1;i >= 0; i--)
        {
            double sum = c[i][n + 1];
            for (int k = i + 1;k <= n; k++)
            {
                sum -= c[i][k] * b[k];
            }
            b[i] = sum / c[i][i];
        }
    }