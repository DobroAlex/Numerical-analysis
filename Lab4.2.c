/* 
 * File:   Lab4.1
 * Author: DobroAlex
 *
 * Created on 26 ноября 2017 г., 20:03
 */

#include <stdio.h>
#include <stdlib.h>

#include "C_Plot.h" //если рисуете под Пингвином 

#define MINX .0
#define MINY .0
#define MAXX 4.
#define MAXY 4.
#define MY_VAR 7
double h[100], s[100], x[] = {  -1., -.5 , .0, .5 , 1. }, y[] = {.0 , .7, 1. , .7, .0};// x[] -- точки графика на оси X y[] -- соответствующие значения на ОУ
double S1 = .0, S2 = 0.; //значения производных в двух точках
const double S1Nature = .0, S2Nature = .0; //при естественном сплайне полагаем значения производных = 0 
void progonka (  double x [],   double y [],   double h [],  double  S1, double    S2);// та самая прогонка
void form (double a[], double  b[], double c [], double f [],  double x [], double y [], double h [], double S1, double S2 );
double Si (double x [], double y [], double s [], double h [], int i, double xx);
int n = 4;

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
        //double h[100], s[100], x[] = {-2. , -1. , .0, 1. , 2.}, y[] = {.0 , .7, 1. , .7, .0};// x[] -- точки графика на оси X y[] -- соответствующие значения на ОУ
        //double S1 = .0, S2 = 10.; //значения производных в двух точках

            
            for (int i = 1; i <= n; i++)
            {
                h[i] = x[i] - x[i - 1]; //дельта между каждым шагом
            }
            progonka(x, y, h, 0, 0);

            for (int i = 0;i <= n; i++) {
                printf ("\t s[%d] = %lf", i, s[i]);
            }
            pl_pencolorname_r (plotter, "red");
            printf ("\nТочки графика : ");
            for (int i = 0; i <= n; i++)
            {

                pl_fmarker_r(plotter, x[i] + fabs((MAXX-MINX)/2), y[i] + fabs((MAXY-MINY)/2.), 16,  .075);
                printf ("\tx[%d] =  %lf , y[%d] = %lf", i, x[i], i,  y[i]);
            }
            pl_pencolorname_r (plotter, "blue");
            printf ("\nТаблица точек кубического сплайна :\n");
            for (int  i = 1; i <= n; i++)
            {
                for (int j = (int)(x[i - 1] * 10000.0); j <= (int)(x[i] * 10000.0); j++ )
                {
                    double x1 = 1.0E-4 * (double)j;
                    double y1 = Si(x, y, s, h, i, x1);
                    pl_pencolorname_r (plotter, "green");
                    pl_fline_r(plotter, 1.0E-4*(double)(j-1)+fabs((MAXX-MINX)/2), Si(x, y, s, h, i, 1.0E-4*(double)(j-1))+ fabs((MAXY-MINY)/2.), x1+fabs((MAXX-MINX)/2), y1+ fabs((MAXY-MINY)/2.) );
                    printf ("\ni = %d, x1 = %lf, y1 = %lf ", i, x1, y1);
                }
            }
            for (int i = 1; i <= n; i++)
            {
                h[i] = x[i] - x[i - 1]; //дельта между каждым шагом
            }
            progonka(x, y, h, S1, S2);
            s[0] = s[1];
            s[n-1] = s[n];
            for (int i = 0;i <= n; i++) {
                printf ("\t s[%d] = %lf", i, s[i]);
            }
            pl_pencolorname_r (plotter, "red");
            printf ("\nТочки графика : ");
            for (int i = 0; i <= n; i++)
            {

                pl_fmarker_r(plotter, x[i] + fabs((MAXX-MINX)/2), y[i] + fabs((MAXY-MINY)/2.), 16,  .075);
                printf ("\tx[%d] =  %lf , y[%d] = %lf", i, x[i], i,  y[i]);
            }
            pl_pencolorname_r (plotter, "blue");
            printf ("\nТаблица точек кубического сплайна :\n");
            for (int  i = 1; i <= n; i++)
            {
                for (int j = (int)(x[i - 1] * 10000.0); j <= (int)(x[i] * 10000.0); j++ )
                {
                    double x1 = 1.0E-4 * (double)j;
                    double y1 = Si(x, y, s, h, i, x1);
                    pl_pencolorname_r (plotter, "blue");
                    pl_fline_r(plotter, 1.0E-4*(double)(j-1)+fabs((MAXX-MINX)/2), Si(x, y, s, h, i, 1.0E-4*(double)(j-1))+ fabs((MAXY-MINY)/2.), x1+fabs((MAXX-MINX)/2), y1+ fabs((MAXY-MINY)/2.) );
                    printf ("\ni = %d, x1 = %lf, y1 = %lf ", i, x1, y1);
                }
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
       return (0);
}

void form (double a[], double  b[], double c [], double f [],  double x [], double y [], double h [], double S1, double S2 )
{
    a[0] = .0;
    b[0] = 2.;
    c[0] = 1.;
    f[0] = 6. * ((y[1] - y[0]) / pow(h[1], 2.) - S1 / pow(h[1], 2.));
    for (int i = 1; i <  n; i++)
    {
            a[i] = h[i];
            b[i] = 2.0 * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6.0 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
        
    }
    a[n] = 1.;
    b[n] = 2.;
    c[n] = .0;
    f[n] = -6. * ((y[n] - y[n - 1]) / pow(h[n], 2.0) - S2 / pow(h[n], 2.0));
}

void progonka (  double x [],   double y [],   double h [],  double  S1, double    S2)// та самая прогонка Важно понять, что при использовании массива в качестве аргумента функции происходит передача в функцию его адреса. Это означает, что код внутри функции действует и может изменять настоящее значение массива, используемого при вызове.
{
    double a[100];
    double b[100];
    double c[100];
    double f[100];
    double p[100];
    double q[100];
    form(a,b,c,f,x,y,h, S1, S2);
    for (int i = 0; i <= n; i++)
    {
        printf ("\n i = %d , a = %lf , b = %lf, c = %lf, f = %lf", i, a[i], b[i], c[i], f[i]);
    }
    p[1] = (- c[0]) / b[0];
    q[1] = f[0] / b[0];
    for (int  i = 0; i < n; i++)
    {
        double r = b[i] + a[i] * p[i];
        p[i + 1] = (- c[i]) / r;
        q[i + 1] = (f[i] - a[i] * q[i]) / r;
    }
    s[n] = ((- a[n]) * q[n] + f[n]) / (b[n] + a[n] * p[n]);
    for (int i = n; i > 0; i--)
    {
        s[i - 1] = p[i] * s[i] + q[i];
    }
}
double Si (double x [], double y [], double s [], double h [], int i, double xx)
{
    return (s[i - 1] * pow(x[i] - xx, 3.0) + s[i] * pow(xx - x[i - 1], 3.0) + (xx - x[i - 1]) * (6.0 * y[i] - h[i] * h[i] * s[i]) + (x[i] - xx) * (6.0 * y[i - 1] - h[i] * h[i] * s[i - 1])) / (6.0 * h[i]);
}