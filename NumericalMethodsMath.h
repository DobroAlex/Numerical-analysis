//������������ ���� ��� ��������� �������, ������� github : DoborAlex. ��� ������ ����������� ��� ������������� ����� ��������� � ���������������� .cpp �����. 
#pragma once 
//��������, �������� ������ ��� �������������, ���� �������������� MVS � GCC
//������������! ���� �� ���� (__MYMATH_H) ��� �� �����

#ifndef __NUMERICALMETHODS_H 
#define __NUMERICALMETHODS_H 

#define MY_PI 3.14159265358979323846 //��
#define MY_E 2.71828182845904523536 // ����������
#define MY_DUB_PI 6.28318530717958623199//��*2
#define MY_REV_E 0.36787944117144233402 // e^-1
#include "stdafx.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
extern int iterations; //����� �������� � normExp
extern clock_t globalT; //���������� ��������� �������
extern double wastedTime; // ���������� ����������, ���������� ����� ����� �������� startClock � stopClock;
namespace NumMet {
	void startClock(void);	//��������� ������
	void stopClock(void);	//������������� ������
	double factorial(int x);
	double bydloExp(double x); //�����-������� ���������� ����������. ������ int_max �������� ��� ����� �������� ��������� �������� � etc
	double normExp(double x); //���������� ������� ��� ����������. �������� ������ �������� ���� ��������� ������� : ���� k-�� ���� �������� <= �������, �� ��������� �������� ����
	double bydloCos(double x); // � �������� ���������, �� ��� ����� �������������
	double pereodicCos(double x);//���� ������������� 
	double periodicSin(double x); //����� ����� � ������ ������������� 
}
#endif