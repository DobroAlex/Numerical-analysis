// Lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"	//для MVS
#include <iostream>
#include <cstdint>
#include <cctype>
using namespace std;
template  <class T> T machineZero(void) {
	T e0 = (T) 0.0F;
	
	for (T e1 = (T) 1.0F; e1 > (T) 0.0F; e1 /= (T) 2.0F) {
	   e0 = e1;
   }
   return e0;
}

template <class T> T machineEpsilon(void) {
	T ep0 = (T) 0.0F;
	T ep = (T) 1.0F;
	for (T f = (T) 1.0F + ep; f > (T) 1.0F; f = (T) 1.0F + ep) {
		ep0 = ep;
		ep /= (T) 2.0F;
	}
	return ep;
}

int main()
{
	cout << "Positive limit for type  double : " << machineZero <double>() << endl;
	cout << "Positive limit for type float : " << machineZero <float> ( ) << endl;
	cout << "Positive limit for type long double : " << machineZero <long double>() << endl; // можно видеть, что MVS не делает разницы между double и LF даже для x64 набора комнад
	cout << "Machine epsilon for double : " << machineEpsilon <double>() << endl;
	cout << "Machine epsilon for float : " << machineEpsilon <float>() << endl;
	system("PAUSE");
	return 0;
}

