
/* 
 * File:   C_Plot.h
 * Author: GitHub@DobroAlex
 *
 * Created on 19 ноября 2017 г., 11:34
 */
/*REQUIREMENTS  :  libplot-dev, libplot2c2, libploticus0, libploticus0-dev , plotutils*/
/*WARNING : to compile this header, U need to add "-lplot -lXaw -lXmu -lXt -lSM -lICE -lXext -lX11 -lpng -lz -lm" for gcc/C 
 and "   -lplotter -lXaw -lXmu -lXt -lSM -lICE -lXext -lX11 -lpng -lz -lm" for g++/C++*/
#ifndef C_PLOT_H
#define C_PLOT_H
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <plot.h>
#ifdef __cplusplus
extern "C" {
#endif
 /*TODO: переписать передачу параметра правильно*/   int initPlot(plPlotter *plott, plPlotterParams *plott_params, double minX, double minY, double maxX, double maxY, double thickness, const char * color  )
    {
        /* set a Plotter parameter */
       plott_params = pl_newplparams ();
       pl_setplparam (plott_params, "PAGESIZE", (char*)"letter");
     
       /* create a Postscript Plotter that writes to standard output */
       if ((plott = pl_newpl_r ("X", stdin, stdout, stderr,
                                  plott_params)) == NULL)
         {
           fprintf (stderr, "Couldn't create Plotter\n");
           return 1;
         }
     
       if (pl_openpl_r (plott) < 0)      /* open Plotter */
         {
           fprintf (stderr, "Couldn't open Plotter\n");
           return 1;
         }
       pl_fspace_r (plott, minX, minY, maxX, maxY); /* set coor system */
       
       pl_flinewidth_r (plott, thickness);    /* set line thickness */
       pl_pencolorname_r (plott, color); /* use red pen */
       pl_erase_r(plott);
       return 0; //if everyting is fine
    }
    void drawAxises(plPlotter * plotter, double minX, double minY, double maxX, double maxY,double thick,  const char* color) //рисует оси. OX э [minX, maxX], OY э [minY, maxY] цвета color
 {

    pl_endpath_r(plotter);
    pl_pencolorname_r(plotter, color);
    pl_flinewidth_r (plotter, thick);
    pl_fline_r(plotter, minX, fabs(maxY-minY)/2., maxX, fabs(maxY-minY)/2.);
    pl_endpath_r(plotter);
    pl_fline_r(plotter, fabs(maxX-minX)/2., minY, fabs(maxX-minX)/2., maxY);
    pl_endpath_r(plotter);
 }
void drawSegsX(plPlotter * plotter, double xStart,  double xEnd, double y, double step, double len, const char * color ) // рисует засечки по оси Х  на высоте  Y длины len  ( len вверх, пол len , шаг step, цвет color 
  {
      pl_endpath_r(plotter);
      pl_pencolorname_r(plotter, color);
      for (double i = xStart; i <= xEnd; i += step ) {
          pl_endpath_r(plotter);
          pl_fline_r(plotter, i, y + len , i, y - len);
          pl_endpath_r(plotter);
      }
      pl_endpath_r(plotter);
}
void drawSegsY (plPlotter * plotter, double yStart, double yEnd, double x, double step, double len, const char * color)//рисует засечки  по оси У по широте X длины len
  {
      pl_endpath_r(plotter);
      pl_pencolorname_r(plotter, color);
      for (double i = yStart; i <= yEnd; i += step ) {
          pl_endpath_r(plotter);
          pl_fline_r(plotter,  x + len/2., i ,    x - len/2. , i );
          pl_endpath_r(plotter);
      }
      pl_endpath_r(plotter);
  }
double toScreenCoordX(const double x, double minX, double maxX) //возвращает экранную координату X
{
    return x + fabs((maxX-minX)/2.);
}
double toScreenCoordY(const double y, double minY, double maxY) //возвращает экранную координату Y
{
    return y + fabs((maxY-minY)/2.);
}
#ifdef __cplusplus
}
#endif

#endif /* C_PLOT_H */

