#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
const int n=4;
int i, j, m, k;
double aa, bb;

double a[n][n+1]={{  3,   4, -9,   5, -14},   //матрица коэффициентов, где последний столбец - правая часть системы
{-15, -12,  50, -16, 44}, 
{-27, -36,  73,   8, 142},
{  9,  12, -10, -16, -76}};
 
int main()
{
    setlocale(LC_ALL, "Russian");
    double* x; 
    x = (double *)malloc(n* sizeof(double));
 
    for (k = 0; k<n; k++) //Поиск максимального элемента в первом столбце
    {
        aa = abs(a[k][k]);
        i = k;
        for(m = k+1; m<n; m++)
            if(abs(a[m][k])>aa)
            {
                i = m;
                aa = abs(a[m][k]);
            }
        cout << "\nНайденный максимальный эл-т на текущей итерации:"<<aa; 
            if (aa == 0)   //проверка на нулевой элемент
            {
                cout<<"Система не имеет решений"<<endl;
            }
 
            if (i != k)  //  перестановка i-ой строки, содержащей главный элемент k-ой строки
            {
                for (j=k; j < n+1; j++)
                {
                    bb = a[k][j];
                    a[k][j] = a[i][j];
                    a[i][j] = bb;
                }
            }
        cout << "\nпосле перестановки строк м-ца A:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                cout << a[i][j] << "  ";
            }
            cout << '\n';
        }
            aa = a[k][k];//преобразование k-ой строки (Вычисление масштабирующих множителей)
            a[k][k] = 1;   
            for (j=k+1;j<n+1;j++) 
                a[k][j] = a[k][j]/aa;
            for (i = k+1; i < n; i++)//преобразование строк с помощью k-ой строки
            {
                bb = a[i][k];
                a[i][k] = 0;
                if (bb!=0)
                    for (j=k+1; j< n+1; j++)
                        a[i][j]=a[i][j]-bb*a[k][j];
            }
    }
 
    for (i=n-1; i>=0; i--)   //Нахождение решений СЛАУ
    {
        x[i] = 0;
        aa = a[i][n];
        for (j = n; j>i; j--) 
            aa = aa-a[i][j]*x[j];
        x[i] = aa;
    }
 
    cout<<"Решение системы:"<<endl;  //вывод решений
    for (i = 0; i< n; i++)
    {
        cout<<"x["<<i+1<<"]="<<x[i];
        cout<<endl;
    }
    //system("PAUSE");
}