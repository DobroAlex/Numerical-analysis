using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Lab9Task1
{
    class Program
    {
        static void Main(string[] args)
        {
            int p = 0;
            int n = int.Parse(Console.ReadLine());
            double eps = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            double[] xk2 = new double[n];
            double[] xk1 = new double[n];
            for (int i = 0; i < n; i++)
            {
                xk1[i] = 1.0;
            }
            double[,] A = new double[n, n];
            for (int  i = 0; i <n;i++)
            {
                for (int j = 0; j <n;j++)
                {
                    A[i,j] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture); 
                }
            }
            double sz1 = 0, sz2 = sz1;
            for (int i = 0; i < n; i++)
            {
                xk2[i] = 0;
                for (int j = 0; j < n; j++)
                {
                    xk2[i] += A[i,j] * xk1[j];
                }
    
            }
            sz1 = xk2[0] / xk1[0];
            while (p == 0)
            {
                for (int i = 0; i < n; i++)
                {
                    xk1[i] = xk2[i];
                }
            
            for (int i = 0; i < n; i++)
            {
                xk2[i] = 0;
                for (int j = 0; j < n; j++)
                {
                    xk2[i] += A[i,j] * xk1[j];
                }
                
            }
            sz2 = xk2[0] / xk1[0];
            if (Math.Abs(sz2 - sz1) < eps) p = 1;
            sz1 = sz2;
        }
            Console.WriteLine("ans = " + sz2);
            Console.ReadKey();
        }
    }
}
