

/* 
 * File:   Lab4.2.c
 * Author: GitHub@DobroAlex
 *
 * Created on 17 декабря 2017 г., 18:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "C_Plot.h"
#define MINX .0
#define MINY .0
#define MAXX 4.
#define MAXY 4.
double x[100], s1[100], s2[100], h[100], temp[100], y[] = {0.5, 0.8, 0.4, 0.8, 0.5};
double h1;
int n = 4;
void form1(double* a, double* b, double* c, double* f, double* x, double* y, double* h);
void form2(double* a, double* b, double* c, double* f, double* x, double* y, double* h);
void progonka1(double* x, double* y, double* h);
void progonka2(double* x, double* y, double* h);
double Si (double x [], double y [], double s [], double h [], int i, double xx);
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
    h1 = 2. / n; 
    for (int i = 0; i <= n ; i++)
    {
        x[i] = -1. + i * h1;
        h[i] = h1;
    }
    progonka1(x, y, h);
    progonka2(x, y, h);
    for (int  i = 0; i <= n; i++)
    {
        printf ("s1[%d] = %lf, s2[%d] = %lf\n", i, s1[i], i , s2[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for ( int j2 = (int)(x[i - 1] * 1000.0); j2 <= (int)(x[i] * 1000.0); j2++)
        {
            double x12 = 1.0E-5 * (double)j2;
            double y1 = Si(x, y, s1, h, i, x12);
            double x12prev = 1.0E-5 * (double)(j2-1);
            double y1prev = Si(x, y, s1, h, i, x12prev);
            pl_pencolorname_r (plotter, "blue"); /* use red pen */
            //pl_fmarker_r(plotter, x[i-1] + fabs((MAXX-MINX)/2), y[i-1] + fabs((MAXY-MINY)/2.), 19,  .15);
            pl_fmarker_r(plotter, toScreenCoordX(x[i-1], MINX, MAXX), toScreenCoordY(y[i-1], MINY, MAXY), 19, .15);
            //pl_fline_r(plotter,toScreenCoordX(x12prev, MINX, MAXX), toScreenCoordY(y1prev, MINY, MAXY), toScreenCoordX(x12, MINX, MAXX), toScreenCoordY(y1, MINY, MAXY));
            //pl_fline_r(plotter, x12prev+ fabs((MAXX-MINX)/2), y1prev+fabs((MAXY-MINY)/2.), x12+ fabs((MAXX-MINX)/2), y1+fabs((MAXY-MINY)/2.));
        }
        
        
    }
    printf ("\nStep2:\n");
    for (int i = 1; i<=n;i++)
    {
        for (int j3 = (int)(x[i - 1] * 1000.0); j3 <= (int)(x[i] * 1000.0); j3++)
        {
            double x12 = 1.0E-5 * (double)j3;
            double y1 = Si(x, y, s2, h, i, x12);  
            double x12prev = 1.0E-5 * (double)(j3-1);
            double y1prev = Si(x, y, s2, h, i, x12prev); 
            printf ("\t x12 = %lf, y1 =%lf",x12, y1);
            pl_pencolorname_r (plotter, "red"); /* use red pen */        
            //pl_fmarker_r(plotter, x[i-1] + fabs((MAXX-MINX)/2), y[i-1] + fabs((MAXY-MINY)/2.), 16,  .075);
            pl_fmarker_r(plotter, toScreenCoordX(x[i-1], MINX, MAXX), toScreenCoordY(y[i-1], MINY, MAXY), 16, .075);
            //pl_fmarker_r(plotter, toScreenCoordX(x12, MINX, MAXX), toScreenCoordY(y[i-1], MINY, MAXY), 1, 0.5);
            pl_fline_r(plotter, (1.0E-5 * (double)(j3-1)) + fabs(MAXX-MINX)/2., Si(x, y, s2, h, i, x12prev) + fabs (MAXY-MINY)/2., x12 + fabs(MAXX-MINX)/2., y1 + fabs (MAXY-MINY)/2.);
            
        }
        pl_fmarker_r(plotter, toScreenCoordX(x[n], MINX, MAXX), toScreenCoordY(y[n], MINY, MAXY), 16, .075);
        
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
    double a[100];
    double b[100];
    double c[100];
    double f[100];
    double p[100];
    double q[100];
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
        double a[100];
        double b[100];
        double c[100];
        double f[100];
        double p[100];
        double q[100];
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