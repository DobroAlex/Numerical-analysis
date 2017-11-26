

/* 
 * File:   Lab4.1
 * Author: DobroAlex
 *
 * Created on 26 ноября 2017 г., 20:03
 */

#include <stdio.h>
#include <stdlib.h>
#include "C_Plot.h"
#define MINX .0
#define MINY .0
#define MAXX 4.
#define MAXY 4.
#define MY_VAR 7
void progonka (const double x [], const double y [], const double h [], double S1, double S2);// та самая прогонка
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
        double h[100], s[100], x[] = {-2. , -1. , .0, 1. , 2.}, y[] = {.0 , .7, 1. , .7, .0};// x[] -- точки графика на оси X y[] -- соответствующие значения на ОУ
        double S1 = .0, S2 = 10.; //значения производных в двух точках
        int n = 4;
        for (int i = 1; i <= n; i++)
        {
            h[i] = x[i] - x[i - 1]; //дельта между каждым шагом
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

void progonka (const double x [], const double y [], const double h [], double S1, double S2)// та самая прогонка Важно понять, что при использовании массива в качестве аргумента функции происходит передача в функцию его адреса. Это означает, что код внутри функции действует и может изменять настоящее значение массива, используемого при вызове.
{
    double * a = (double *) malloc(100 * sizeof(double));
    double * b = (double *) malloc(100 * sizeof(double));
    double * c = (double *) malloc(100 * sizeof(double));
    double * f = (double *) malloc(100 * sizeof(double));
    double * p = (double *) malloc(100 * sizeof(double));
    double * q = (double *) malloc(100 * sizeof(double));
    
    
    
    
    free (a);
    free (b);
    free (c);
    free (f);
    free (p);
    free (q);
   
}