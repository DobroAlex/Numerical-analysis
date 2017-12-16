#include <iostream>
#include <math.h>
using namespace std;
double testF(double x){
	return  (double)sin(x)/x; 
}
int main(){
	int n =5;
	double h=0.2;
	double y_values[n];
	double v=0.1;
	double sum=0;
	double res;
	for (int i =0; i < 5; i++){
		y_values[i] = testF(v);
		v+=h;
		sum+=y_values[i];
	}
	res=h*sum;
		printf("%f\n",res);

	return 0;
}