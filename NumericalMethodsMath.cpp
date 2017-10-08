#include "stdafx.h"
#include "NumericalMethodsMath.h"
int iterations; //число итераций в normExp
clock_t globalT; //глобальна€ структура времени
double wastedTime; // глоабльна€ переменна€, указывюща€ врем€ между вызовами startClock и stopClock;

void  NumMet::startClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	 ::globalT = clock();
}
void  NumMet::stopClock(void) {		//http://www.cplusplus.com/reference/ctime/clock/
	 ::globalT = clock() -  ::globalT;
	 ::wastedTime = ((double) ::globalT) / CLOCKS_PER_SEC;
}
double   NumMet::bydloExp(double x) {
	double exp = 0;
	if (x >= 0) {
		for (int k = 0; k <= 170; k++) { //после 170 есть риск переполнить double при вычислении факториала 
			exp += pow(x, (double)k) / NumMet::factorial(k);
		}
	}
	else {
		return (1 / NumMet::bydloExp(abs(x)));
	}
	return exp;
}
double   NumMet::factorial(int x) {
	double f = 1;
	for (int i = 2; i <= x; i++)
	{
		f *= i;
	}
	return (double)f;
}
double   NumMet::normExp(double x) {
	double exp = 0;
	double prevStep = 0;
	if (x >= 0) {
		for (int k = 0; exp != exp + pow(x, (double)k) / NumMet::factorial(k); k++) {
			exp += pow(x, (double)k) / NumMet::factorial(k);
			 ::iterations = k;
		}
	}
	else {
		return  NumMet::normExp(abs(x));
	}
	return exp;
}
double  NumMet::bydloCos(double x) { // >30 начинает сильно отклон€тьс€, две цифры после зап€той уже тер€ютс€
	double ans = 0;
	for (int k = 0; ans != ans + (pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / NumMet::factorial(2.0 * (double)k); k++) {
		ans += (double)(pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / NumMet::factorial(2.0 * (double)k);
		 ::iterations = k;
	}
	return ans;
}
double  NumMet::pereodicCos(double x) {
	while (x >= MY_DUB_PI)
	{
		x -= MY_DUB_PI;
	}
	double ans = 0;
	for (int k = 0; ans != ans + (pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / NumMet::factorial(2.0 * (double)k); k++) {
		ans += (double)(pow(-1.0, (double)k) * pow((double)x, 2.0*(double)k)) / NumMet::factorial(2.0 * (double)k);
		 ::iterations = k;
	}
	return ans;
}
double   NumMet::periodicSin(double x) {
	while (x >= 2.0 * MY_PI) {
		x -= 2.0 * MY_PI;
	}
	double ans = 0;
	for (int k = 0; ans != ans + (pow(-1.0, (double)k) * pow((double)x, (double)(2.0*k + 1))) / factorial((double)(2.0*k + 1)); k++) {
		ans += (pow(-1.0, (double)k) * pow((double)x, (double)(2.0*k + 1))) / NumMet::factorial((double)(2.0*k + 1));
		 ::iterations = k;
	}
	return ans;
}