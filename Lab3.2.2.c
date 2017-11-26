
/* 
 * File:   Lab3.2.2.c
 * Author: GitHub@dobroalex
 *
 * Created on 19 ноября 2017 г., 15:18
 */

#include "C_Plot.h"
#define MINX .0
#define MINY .0
#define MAXX 4.
#define MAXY 4.
#define MY_VAR 23
double f(double x);//несколько абстрактная ф-ция f(x) из  первой части второго задания. 
double f1(double x); // 1/1(1+dx^2)
double Hn(double x, double a, double b); //ф-ла (3) из теории 
double h;

int main(int argc, char** argv) {
    int n = 3; //кратность производной?
    int X[100], Y[100];
        h = 2. / (double)n;
        for (int  i = 0 ; i <= n; i++)
        {
            X[i] = -1.0 + (double)i * h;
            Y[i] = f(X[i]);
        }
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
       while (n != 1488)
       {
            for (int j = -10000; j <= 10000; j++ )
            {
                double x1 = 1.0E-4 * (double)j;
                double y2 = f(x1);
                printf("x1 = %lf", x1);
                printf("\ty2=%lf\n", y2);
                pl_pencolorname_r (plotter, "red");
                pl_fpoint_r(plotter, x1+fabs(MAXX-MINX)/2., (y2)+fabs(MAXY-MINY)/2.); // корректное отображение относительно OX,OY
            }
            int i  = 0;
            while ( i < n)
            {
                int j2 = (int) (X[i]*100000.);
                while (j2 <= (int) (X[i+1]*100000.))
                {
                    double x12 = 1.0E-5 * (double)j2;
                    double y1 = Hn(x12, X[i], X[i + 1]);
                    pl_pencolorname_r (plotter, "blue");
                    pl_fpoint_r(plotter, x12+fabs(MAXX-MINX)/2., y1+fabs(MAXY-MINY)/2.); // корректное отображение относительно OX,OY
                    //pl_fcircle_r(plotter, X[n]+fabs(MAXX-MINX)/2., Y[n]+fabs(MAXY-MINY)/2., .03);
                    j2++;
                }
                
                i++;
                
            }
            scanf("%d", &n);
            h = 2. / (double)n;
            for (int  i = 0 ; i <= n; i++)
            {
                X[i] = -1.0 + (double)i * h;
                Y[i] = f(X[i]);
            }
            pl_erase_r (plotter);  
            drawAxises(plotter, MINX, MINY, MAXX, MAXY, 0.01, "black");
            drawSegsX(plotter, MINX, MAXX, fabs(MAXY-MINY)/2., fabs((MAXX-MINX)/(MAXX-MINX)), .5, "black");
            drawSegsY(plotter, MINY, MAXY, fabs(MAXX-MINX)/2.,  fabs((MAXY-MINY)/(MAXY-MINY)), .5, "black");
            pl_endpath_r(plotter);

       }
       printf("Finished");
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
    return 1. / (1. +  MY_VAR*pow(x, 2.));
}
double Hn(double x, double a, double b) { //ф-ла (3) из теории 
    //double h1 = b -a ;
    //double k = (x - a) / h1;
    double k = (x-a)/h;
    
    return (1. - 3. * pow(k, 2.) + 2 *  pow(k, 3.)) * f(a) + (3. * pow(k, 2.)  - 2. * pow(k, 3.)) * f(b) + h* (k - 2. * pow(k, 2.) + pow(k, 3.)) * f1(a ) + h * (-1.*pow(k, 2.) + pow(k, 3)) * f1(b);
} 
double f1(double x) // 1/1(1+dx^2)
{
    
    return (-2*MY_VAR*x)/pow( (1. + 23. * pow(x, 2.)), 2.);
}

