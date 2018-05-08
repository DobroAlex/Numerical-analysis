/*https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%93%D0%B0%D1%83%D1%81%D1%81%D0%B0_%E2%80%94_%D0%97%D0%B5%D0%B9%D0%B4%D0%B5%D0%BB%D1%8F_%D1%80%D0%B5%D1%88%D0%B5%D0%BD%D0%B8%D1%8F_%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%8B_%D0%BB%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D1%8B%D1%85_%D1%83%D1%80%D0%B0%D0%B2%D0%BD%D0%B5%D0%BD%D0%B8%D0%B9*/
using System;

namespace GauSSSeidel_Method
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Input matrix size:");
            int n = int.Parse(Console.ReadLine());
            Console.WriteLine("Input calculation accuracy:");
            double eps = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            double[,] A = new double[n, n];
            Console.WriteLine("Input matrix A:");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A[i, j] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
                }
            }
            double[] b = new double[n]; //Столбец правых частей
            Console.WriteLine("Input The right-hand column:");
            for (int i = 0; i < b.Length;i++)
            {
                b[i] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            double[] x = new double[n]; //текущее
            double[] p = new double[n]; //и предыдущее решение
            Console.WriteLine("Input initial approximation of the decision column:"); //начальное приближение обычно можно делать нулевым
			for (int i = 0; i < x.Length; i++)
			{
				x[i] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
			}
            do
            {
                for (int i = 0; i < n;i++)
                {
					p[i] = x[i];
                }
                for (int i = 0; i < n;i++)
                {
                    var tmp = 0.0;
                    for (int j = 0; j < i;j++)
                    {
                        tmp += A[i, j] * x[j];
                    }
                    for (int j = i + 1; j < n;j++)
                    {
                        tmp += A[i,j] * p[j];
                    }
                    x[i] = (b[i] - tmp) / A[i, i];
                }
            } while (!IsConverege(x, p, eps));
            Console.WriteLine("Answer is:");
            for (int i = 0; i < n;i++)
            {
                Console.WriteLine("x"+i+1+"="+x[i]);
            }
		}
        public static bool IsConverege(double [] xk , double [] xkp, double eps)
        {
			double norm = 0;
            for (int i = 0; i < xk.Length; i++)
			{
				norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
			}
            if (Math.Sqrt(norm) >= eps)
            {
                return false;
            }
			return true;
        }

    }
}
