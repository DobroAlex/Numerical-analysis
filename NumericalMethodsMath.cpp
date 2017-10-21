/*TODO : привести всё к одной кодировке. MVS делает непортабельными комментари со своим  Win-1251*/
#include "NumericalMethodsMath.h"
int iterations; //÷èñëî èòåðàöèé â normExp
clock_t globalT; //ãëîáàëüíàÿ ñòðóêòóðà âðåìåíè
double wastedTime; // ãëîàáëüíàÿ ïåðåìåííàÿ, óêàçûâþùàÿ âðåìÿ ìåæäó âûçîâàìè startClock è stopClock;
long dummy; //для функции rnd();

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
		for (int k = 0; k <= 170; k++) { //ïîñëå 170 åñòü ðèñê ïåðåïîëíèòü double ïðè âû÷èñëåíèè ôàêòîðèàëà 
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
double  NumMet::bydloCos(double x) { // >30 íà÷èíàåò ñèëüíî îòêëîíÿòüñÿ, äâå öèôðû ïîñëå çàïÿòîé óæå òåðÿþòñÿ
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
void NumMet::seed(long d) {
    ::dummy = d;
}
 double NumMet::rnd( ) {   
    /*L'Ecuyer algorithm for uniform random generator with practically endless  // 
 
// period. Combining 2 sequences. */                        
 
    const long IM1 = 2147483563;
 
    const long IM2 = 2147483399;
 
    const double AM = (1./IM1);
 
    const long IMM1 = (IM1 - 1);
 
    const int IA1 = 40014;
 
    const int IA2 = 40692;
 
    const long IQ1 = 53668;
 
    const long IQ2 = 52774;
 
    const int IR1 = 12211;
 
    const int IR2 = 3791;
 
    const int NTAB = 32;
 
    const int NWUP = 8;
 
    const double NDIV = (1 + IMM1 / NTAB);
 
    const double EPS = 1.2e-7;
 
    const double RNMX = (1.0 - EPS);
 
    
 
    static long dummy2 = 123456789;
 
    static long iy = 0;
 
    static long iv[32];
 
 
 
    long k = 0;
 
 
 
    // initialize the random sequence (first set of coefficients, the 
 
    // routine close to that in the function above
 
    if (::dummy <= 0 || !iy)
 
    {
 
        // avoid negative or zero seed
 
        if (::dummy < 0)
 
            ::dummy =- ::dummy;
 
        else
 
            if (!::dummy)
 
                ::dummy = 1;
 
        dummy2 = ::dummy;
 
        // after NWUP warmups, initialize shuffle table
 
        for (int j = NTAB + NWUP - 1; j >= 0; --j)
 
        {
 
            k = ::dummy / IQ1;
 
            if ((::dummy = IA1 * (::dummy - k * IQ1) - IR1 * k) < 0) ::dummy += IM1;
 
            if (j < NTAB) iv[j] = ::dummy;
 
        }
 
        // first specimen from the table
 
        iy = iv[0];
 
    }
 
    // regular work: generate 2 sequences.
 
    k = ::dummy / IQ1;
 
    if ((::dummy = IA1 * (::dummy - k * IQ1) - IR1 * k) < 0) ::dummy+=IM1;
 
    k = dummy2 / IQ2;
 
    if ((dummy2 = IA2 * (dummy2 - k * IQ2) - IR2 * k) < 0) dummy2+=IM2;
 
    // shuffle output combining 2 sequences
 
    int j = 0;
 
    iy = iv[j = iy / NDIV] - dummy2;
 
    iv[j] = ::dummy;
 
    if(iy < 1) iy += IMM1;
 
    // return the result, as in the previous function
 
    double temp;
 
    return (double)(((temp = AM * iy) > RNMX ? RNMX : temp));
 
}
