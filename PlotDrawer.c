 #include <stdio.h>
     #include <plot.h>
#include <math.h>
#include "C_Plot.h"
     #define MAXORDER 12
/*double myExp(double x)
{
    return exp(x);
}*/
// void drawAxises(plPlotter * plotter, double minX, double minY, double maxX, double maxY, const char* color); //рисует оси. OX э [minX, maxX], OY э [minY, maxY] цвета color
// void drawSegsX(plPlotter * plotter, double xStart, double xEnd, double y, double step, double len, const char * color ); // рисует засечки по оси Х  на высоте  Y длины len  (пол len вверх, пол len вниз, шаг step, цвет color 
// void drawSegsY (plPlotter * plotter, double yStart, double yEnd, double x, double step, double len, const char * color); //рисует засечки  по оси У по широте X длины len
 void draw_c_curve (plPlotter *plotter, double dx, double dy, int order)
     {
       if (order >= MAXORDER)
         /* continue path along (dx, dy) */
         pl_fcontrel_r (plotter, dx, dy);
       else
         {
           draw_c_curve (plotter,
                         0.5 * (dx - dy), 0.5 * (dx + dy), order + 1);
           draw_c_curve (plotter,
                         0.5 * (dx + dy), 0.5 * (dy - dx), order + 1);
         }
     }
     
     int main ()
     {
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
       pl_fspace_r (plotter, 0.0, 0.0, 240.0, 320.0); /* set coor system */
       
       pl_flinewidth_r (plotter, 0.25);    /* set line thickness */
       pl_pencolorname_r (plotter, "red"); /* use red pen */
       pl_erase_r (plotter);               /* erase graphics display */
       pl_fmove_r (plotter, 600.0, 300.0); /* position the graphics cursor */
          pl_endpath_r(plotter);
       //initPlot(plotter, plotter_params, 0, 0, 240, 320, .5 , "red");
       drawAxises(plotter,0,0,240,320, "black" );
       drawSegsX(plotter, 0, 240, fabs(320)/2., 10, 10, "red");
       for (int i = 0; i <= 100; i++){
         //  pl_line_r(plotter, i-1, exp(i-1), i, exp(i) );
       }
       drawSegsY(plotter, 0, 320, fabs(240)/2., 10, 10, "red");
       
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
 /*void drawAxises(plPlotter * plotter, double minX, double minY, double maxX, double maxY, const char* color) 
 {
     pl_endpath_r(plotter);
     pl_pencolorname_r(plotter, color);
     pl_line_r(plotter, minX, fabs(maxY-minY)/2., maxX, fabs(maxY-minY)/2.);
     pl_endpath_r(plotter);
     pl_line_r(plotter, fabs(maxX-minX)/2., minY, fabs(maxX-minX)/2., maxY);
     pl_endpath_r(plotter);
 }
  void drawSegsX(plPlotter * plotter, double xStart,  double xEnd, double y, double step, double len, const char * color ) 
  {
      pl_endpath_r(plotter);
      pl_pencolorname_r(plotter, color);
      for (double i = xStart; i <= xEnd; i += step ) {
          pl_endpath_r(plotter);
          pl_line_r(plotter, i, y + len/2. , i, y -len/2.);
          pl_endpath_r(plotter);
      }
      pl_endpath_r(plotter);
  }
  void drawSegsY (plPlotter * plotter, double yStart, double yEnd, double x, double step, double len, const char * color)
  {
      pl_endpath_r(plotter);
      pl_pencolorname_r(plotter, color);
      for (double i = yStart; i <= yEnd; i += step ) {
          pl_endpath_r(plotter);
          pl_line_r(plotter,  x + len/2., i ,    x - len/2. , i );
          pl_endpath_r(plotter);
      }
      pl_endpath_r(plotter);
  }
   */