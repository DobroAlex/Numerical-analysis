// Lab12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <ctime>
#include <limits>
#include <iomanip>
#include <corecrt_math_defines.h>
using namespace std;
template <class T> T machineEpsilon(void) {
	T ep0 = (T) 0.0F;
	T ep = (T) 1.0F;
	for (T f = (T) 1.0F + ep; f > (T) 1.0F; f = (T) 1.0F + ep) {
		ep0 = ep;
		ep /= (T) 2.0F;
	}
	return ep;
}
int iterations; //число итераций в normExp
clock_t globalT; //глобальная структура времени
double wastedTime; // глоабльная переменная, указывющая время между вызовами startClock и stopClock;
inline void startClock(void);	//запускает таймер
inline void stopClock(void);	//останавливает таймер
double factorial(int x);
double bydloExp(double x); //быдло-функция вычисления экспоненты. Делает int_max итераций без учёта сложения машинного эпсилона и etc
double normExp(double x); //нормальная функция для экспоненты. Основной фишкой является учет машинного эпсилон : если k-ый член итерации <= эпсилон, то прерываем сложение ряда
double normCos(double x); // с машинным эпсилоном, но без учета переодичности
double pereodicCos(double x);

int main()
{
	startClock();
	stopClock();
	for (int x = -50; x <= 50; x++) {

		cout << "X = " << x;
		cout <<  ", bydloExp(x) = ";
		startClock();
		cout << std::setprecision(40) << bydloExp(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate ";
		cout << "exp(x) =  ";
		startClock();
		cout << std::setprecision(40) <<  exp(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate ";
		cout << ", normExp(x) = ";
		startClock();
		cout << std::setprecision(40) << normExp(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate " << " iter = " << ::iterations << endl << endl;
	}
	getchar();
	for (int x = -50; x <= 50; x++) {
		cout << "X = " << x;
		cout << ", normCos(x) = ";
		startClock();
		cout << std::setprecision(40) << normCos(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate " << " iter = " << ::iterations<<' ';
		cout << "cos(x) =  ";
		startClock();
		cout << std::setprecision(40) << cos(x);
		stopClock();
		cout << ", pereodCos(x) = ";
		startClock();
		cout << std::setprecision(40) << pereodicCos(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate " << " iter = " << ::iterations << endl << endl;
	}
	getchar();
    return 0;
}

void startClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	::globalT = clock();
}
void stopClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	::globalT = clock() - ::globalT;
	::wastedTime = ((double)::globalT) / CLOCKS_PER_SEC;
}
double bydloExp(double x) {
	double exp = 0;
	if (x >= 0) {
		for (int k = 0; k <= 170; k++) { //после 170 есть риск переполнить double при вычислении факториала 
			exp += pow(x, (double)k) / factorial(k);
		}
	}
	else {
		return (1 / bydloExp(abs(x)));
	}
	return exp;
}
 double  factorial(int x) {
	double f = 1;
	for (int i = 2; i <= x; i++)
	{
		f *= i;
	}
	return (double)f;
}
 double normExp(double x) {
	 double exp = 0;
	 double prevStep = 0;
	 if (x >= 0) {
		 for (int k = 0; exp != exp + pow(x, (double)k) / factorial(k); k++) {
			 exp += pow(x, (double)k) / factorial(k);
			 ::iterations = k;
		 }
	 }
	 else {
		 return normExp(abs(x));
	 }
	 return exp;
 }
 double normCos(double x) { // >30 начинает сильно отклоняться, две цифры после запятой уже теряются
	 double ans = 0;
	 for (int k = 0; ans != ans + (pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / factorial(2.0 * (double)k); k++) {
		 ans += (double)(pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / factorial(2.0 * (double)k);
		 ::iterations = k;
	 }
	 return ans;
}
 double pereodicCos(double x) {
	 while (x >= M_PI * 2.0)
	 {
		 x -= M_PI * 2.0;
	 }
	 double ans = 0;
	 for (int k = 0; ans != ans + (pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / factorial(2.0 * (double)k); k++) {
		 ans += (double)(pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / factorial(2.0 * (double)k);
		 ::iterations = k;
	 }
	 return ans;
 }