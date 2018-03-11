#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "ukr");
    float A[10][10];
    float U[10][10];
    float b[10], x[10], y[10];
    int n, k;
    int i, j;
    float temp;
    cout << "Введите размерность матрицы" << endl;
    cin >> n;
label:
    cout << "Введите элементы мартрицы" << n << "x" << n << endl;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            U[i][j] = 0;
        }
    //Проверка на симметричность
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (A[i][j] != A[j][i])
            {
                cout << "Не симметрична" << endl;
                goto label;
            }
        }
    cout << "Введите вектор b" << n << "x" << n << endl;
    for (i = 0; i < n; i++)
    {
        cin >> b[i];
    }
 
    for (int i = 0; i < n; i++)
    {
        temp = 0;
        for (int k = 0; k < i; k++)
            temp = temp + U[k][i] * U[k][i];
        U[i][i] = sqrt(A[i][i] - temp);
        for (j = i; j < n; j++)
        {
            temp = 0;
            for (k = 0; k < i; k++)
                temp = temp + U[k][i] * U[k][j];
            U[i][j] = (A[i][j] - temp) / U[i][i];
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << U[i][j]<<" ";
        }
        cout << endl;
    }
    for (i = 0; i < n; i++)
    {
        temp = 0;
        for (int k = 0; k < i; k++)
            temp = temp + U[k][i] * y[k];
        y[i] = (b[i] - temp) / U[i][i];
    }
    for (i = n - 1; i >= 0; i--)
    {
        temp = 0;
        for (int k = i + 1; k < n; k++)
            temp = temp + U[i][k] * x[k];
        x[i] = (y[i] - temp) / U[i][i];
    }
    for (i = 0; i < n; i++)
        cout << "x" << i << "= " << x[i] << endl;
    system ("pause");
}

