#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <stdbool.h>
#include <float.h>
int dtoi ( double x); //переносит все числа справа от запятой влево путем последовательного умножения на 10
double Round (double x, int precision);
bool isEqual(double a, double b); //проверяет два double на равенство через машинный эпсилон
double testFunc(double x); //интегрируемая функция
double integrSimpson (double epsilon, double a, double b, double M); //интеграл Симпосна на отрезке a,b, с точностью epsilon. Интегрируемая функция -- double testFunc(x). M  = max[a,b] (производная p раз (для Симпсона 4) f(x), считаем ручками
double centralRect(double a, double b, int n); //центральые прямоугльники на отрезке [a;b]  с разбиением на n отрезков http://mathprofi.ru/metod_prjamougolnikov.html
int main(void) {
	// your code goes here
	for (int n = 0; n <= 20; n++)
	printf ("n = %d, centralRect = %lf, integral = %10.10lf\n", n, centralRect(0,4,n),  (1./sqrt(2*M_PI)) * centralRect(0,4,n)); 
	return 0;
}
double Round (double x, int precision)
{
   int mul = 10;
   
   for (int i = 0; i < precision; i++)
      mul *= mul;
   if (x > 0)
      return floor(x * mul + .5) / mul;
   else
      return ceil(x * mul - .5) / mul;
}

double testFunc(double x)//интегрируемая функция
{
#ifdef DEBUG
    return 1./x;
#endif
    //return sin(x)/x;
    return exp((-x*x)/2.); //подынтегральная часть  ф-ции Лапласа
}
double centralRect(double a, double b,  int n) //центральые прямоугльники на отрезке [a;b]  
{
#ifdef LOG 
    printf ("__________________________\nCENTRAL RECTS \n__________________________\n");
#endif
    //int n = round(1./h);
    double h = (b-a)/n;
#ifdef LOG
    printf ("h = %lf\n", h);
#endif
    double * yVals = (double *) malloc((n+1) * sizeof(double)); //массив значенйи f(x)
    double * xVals = (double *) malloc((n+1) *sizeof(double)); //массив средних точек
    xVals[0] = a;
    for (int i = 1; i <= n; i++)
    {
        xVals[i] = xVals[i-1]+h; 
    }
#ifdef LOG
    for (int i = 0; i <= n; i++)
    {
        printf ("X[%d] = %lf ;", i, xVals[i]);
    }
    printf ("\n");
    for (int i = 0; i < n; i++)
    {
        printf ("X[%d] + h/2 = %lf ;", i, xVals[i] + h/2.);
    }
#endif
    double sum = .0;
    for (int i = 0; i < n ; i++)
    {
        sum += testFunc(xVals[i] + h/2.);
    }
#ifdef LOG
    printf ("\nSum  = %lf\n\n", sum);
#endif
    return h *sum;

}
double integrSimpson (double epsilon, double a, double b, double M) //интеграл Симпосна на отрезке a,b, с точностью epsilon. Интегрируемая функция -- double testFunc(x). M  = max[a,b] (производная p раз (для Симпсона 4) f(x), считаем ручками
{
    const int A = 180; //знаменатель из формулы оценки погрешности
    const int p = 4; // порядок апроксимации
    double h = pow(((A * epsilon)/(fabs(b-a)*M)), 1./p);
    printf ("\nh = %lf",h);
    double S2, S1; //для формулы Рунге
    int n = ceil(((b-a)/h)); //окургляем вверх TODO : спросить, куда правильно окурглять если n не целое 
    printf("\nn=%d\n\n",n);
    double  * x0 =  (double *) malloc( (n+1) * sizeof(double)), *f0 = (double*) malloc((n+1) * sizeof(double));//явный каст для собирающих g++
    double sumOfOdd= .0;
    double sumOfEven = .0;
    //double step = fabs(a-b)/n;
    for (int  i = 0; i <=n; i++)
    {
        x0[i] = a+i*h;
        f0[i] = testFunc(x0[i]);
        printf ("X0[%d] = %f , F0[%d] =  %f\t", i, x0[i], i, f0[i]);
    
    }
    for (int i = 1; i < n; i++)
    {
        if (i == n)
        {
            continue;
        }
        if ( i % 2 == 0)
        {
            sumOfEven += f0[i];
        }
    }
    printf("\n sumOfEven =  %lf\n", sumOfEven);
    for (int  i = 1; i <=n ; i++)
    {
        if (i == n)
        {
            continue;
        }
        if ( i % 2 != 0)
        {
            sumOfOdd += f0[i];
        }
    }
    printf("\n sumOfOdd =  %lf\n", sumOfOdd);
    printf ("h/3 = %lf , f0 = %lf, 4*Odd = %lf, 2 * Even = %lf, fn = %lf ", h/3., f0[0], 4* sumOfOdd, 2 * sumOfEven, f0[n]);
    const double answer = (h/3.) * (testFunc(x0[0]) + 4 * sumOfOdd + 2 * sumOfEven + testFunc(x0[n]));
    printf ("\n Epsilon = %lf , answer = %lf ", epsilon , answer);
    //return (h/3.) * (testFunc(x0[0]) + 4 * sumOfOdd + 2 * sumOfEven + testFunc(x0[n]));
    return answer;
}
bool isEqual(double a, double b) //проверяет два double на равенство через машинный эпсилон
{
    if (fabs(a-b) <= DBL_EPSILON)
    {
        return true;
    }
    return false;
}
int dtoi ( double x) //переносит все числа справа от запятой влево путем последовательного умножения на 10
{
    double right = fabs (x - (int)x);
    while (isEqual(right, .0) == 0) //MAGIC
    {
        x *= 10.;
        right  =  fabs (x - (int)x);
    }
    return (int)x;
}
