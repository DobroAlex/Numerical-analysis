// Lab12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <ctime>
#include <limits>
#include <iomanip>
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
void startClock(void);	//запускает таймер
void stopClock(void);	//останавливает таймер
double factorial(int x);
double bydloExp(int x); //быдло-функция вычисления экспоненты. Делает int_max итераций без учёта сложения машинного эпсилона и etc
double normExp(int x); //нормальная функция для экспоненты. Основной фишкой является учет машинного эпсилон : если k-ый член итерации <= эпсилон, то прерываем сложение ряда
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
    return 0;
}

void startClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	::globalT = clock();
}
void stopClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	::globalT = clock() - ::globalT;
	::wastedTime = ((double)::globalT) / CLOCKS_PER_SEC;
}
double bydloExp(int x) {
	double exp = 0;
	if (x >= 0) {
		for (int k = 0; k <= 170; k++) { //после 170 есть риск переполнить double
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
 double normExp(int x) {
	 double exp = 0;
	 double prevStep = 0;
	 if (x >= 0) {
		 for (int k = 0; k <= 170; k++) {
			 if (k >= 1) {
				 if (pow(x, (double)(k-1)) / factorial(k) - pow(x, (double)k) / factorial(k) >= machineEpsilon<double>() ){
					 break;
				 }
			 }
			 exp += pow(x, (double)k) / factorial(k);
			 ::iterations = k;
		 }
	 }
	 else {
		 return normExp(abs(x));
	 }
	 return exp;
 }