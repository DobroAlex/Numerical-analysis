
/* 
 * File:   Lab3.2.1
 * Author: GitHub@dobroalex
 *
 * Created on 19 ноября 2017 г., 11:56
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "C_Plot.h"
#define MINX .0
#define MINY .0
#define MAXX 10.
#define MAXY 10.

#define MY_VAR 7

double f(double x);//несколько абстрактная ф-ция f(x) из  первой части второго задания. 
double Hn(double x, double a, double b , double pp, double pp1 );//ф-ла (3) из теории 
double h;
int main(int argc, char** argv) {
    double  p1 = 1., p2 = -1.; //выбор точек, p1 = f'(-1), p2 = f'(1)
    int n = 1;
    h = 2./(double)(n);
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
       
    while (p1 != 1488 && p2 != 1488) {
        for (int j = -10000; j <= 10000; j++) {
            double x1 = 1.E-4 * (double)j;
            double y1 =Hn(x1, -1, 1, p1, p2);
            printf("\nx1 = %lf", x1);
            printf("\ty1 = %lf", y1);
            printf("\tj = %d\n", j);
            pl_pencolorname_r (plotter, "red");
            pl_fpoint_r(plotter, x1+fabs(MAXX-MINX)/2., (y1)+fabs(MAXY-MINY)/2.); // корректное отображение относительно OX,OY
        }       
        printf("Current f'(-1) = %lf, f'(1) = %lf\n", p1 , p2);
        printf("Input new f'(-1) and new f'(1)\n");
        scanf("%lf%lf", &p1, &p2);
        pl_erase_r(plotter);
        drawAxises(plotter, MINX, MINY, MAXX, MAXY, 0.01, "black");
        drawSegsX(plotter, MINX, MAXX, fabs(MAXY-MINY)/2., fabs((MAXX-MINX)/(MAXX-MINX)), .5, "black");
        drawSegsY(plotter, MINY, MAXY, fabs(MAXX-MINX)/2.,  fabs((MAXY-MINY)/(MAXY-MINY)), .5, "black");
    }
    printf("End");
    
    
    
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
double f(double x){ //несколько абстрактная ф-ция f(x) из  первой части второго задания. 
    return 1. / (1. + (5. + MY_VAR)*pow(x, 2.));
}
double Hn(double x, double a, double b, double pp, double pp1) { //ф-ла (3) из теории 
    double h1 = b -a ;
    double k = (x - a) / h1;
    return (1. - 3. * pow(k, 2.) + 2 *  pow(k, 3)) * f(a) + (3. * pow(k, 2)  - 2 * pow(k, 3.)) * f(b) + h* (k - 2. * pow(k, 2.) + pow(k, 3.)) * pp + h * (-pow(k, 2.) + pow(k, 3)) * pp1;
} 
