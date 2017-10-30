//Заголовочный файл для численных методов, написан github : DoborAlex. Эта строка обязательна для использвоания этого заголовка и соответствующего .cpp файла. 
#pragma once 
//возможно, придется убрать для совместимости, хотя поддерживается MVS и GCC
//Препроцессор! Если ты меня (__MYMATH_H) ещё не видел

#ifndef __NUMERICALMETHODS_H 
#define __NUMERICALMETHODS_H 

#define MY_PI 3.14159265358979323846 //Пи
#define MY_E 2.71828182845904523536 // Экспонента
#define MY_DUB_PI 6.28318530717958623199//Пи*2
#define MY_REV_E 0.36787944117144233402 // e^-1
//#include "stdafx.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstdlib>
extern int iterations; //число итераций в normExp
extern clock_t globalT; //глобальная структура времени
extern double wastedTime; // глоабльная переменная, указывющая время между вызовами startClock и stopClock;
extern long dummy; //для функции rnd();
namespace NumMet {
	void startClock(void);	//запускает таймер
	void stopClock(void);	//останавливает таймер
	double factorial(int x);
	double bydloExp(double x); //быдло-функция вычисления экспоненты. Делает int_max итераций без учёта сложения машинного эпсилона и etc
	double normExp(double x); //нормальная функция для экспоненты. Основной фишкой является учет машинного эпсилон : если k-ый член итерации <= эпсилон, то прерываем сложение ряда
	double bydloCos(double x); // с машинным эпсилоном, но без учета переодичности
	double pereodicCos(double x);//учёт переодичности 
	double periodicSin(double x); //синус сразу с учётом переодичности 
        void seed(long d); //семя для double rnd(). Лучше задавать через time(NULL);
        double rnd(); //генератор случайных double чисел
        int lenBetweenpoints (int x1, int x2); //расстояние между двумя точками на координатной прямой, добавлено для скорости в  2.1
/*TODO:*/        double lagranz(double t, double * X, double *Y, double n  ); //интерполяциооный многочлен Лагранжа по массиву размера n  в точке t 
/*Переписать t на x, n на size */
}
#endif