// Lab12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <ctime>
#include <limits>
#include <iomanip>
#include "NumericalMethodsMath.h"

using std::cin;
using std::cout;
using std::endl;
using namespace NumMet;


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
		cout << ", it took " << std::setprecision(40) << ::wastedTime << " seconds to calculate ";
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
		cout << ", bydloCos(x) = ";
		startClock();
		cout << std::setprecision(40) << bydloCos(x);
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
	for (int x = -50; x <= 50; x++) {
		cout << "X = " << x;
		cout << ", pereodicSin(x) = ";
		startClock();
		cout << std::setprecision(40) << periodicSin(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate " << " iter = " << ::iterations << ' ';
		cout << "sin(x) =  ";
		startClock();
		cout << std::setprecision(40) << sin(x);
		stopClock();
		cout << ", it took " << std::setprecision(40) << wastedTime << " seconds to calculate " << endl << endl;
	}
	getchar();
    return 0;
}

