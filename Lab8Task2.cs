using System;

namespace Lab8Task2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.BackgroundColor = ConsoleColor.DarkCyan;
            int n = 0;
            double eps = 0;
            Console.WriteLine("Input square matrix size:\n");
#region
            try
            {
                n = int.Parse(Console.ReadLine());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + "Aborting");
                Environment.Exit(-1);
            }

            Console.WriteLine("Input calculation accuracy:\n");
            try
            {
                eps = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + "Aborting");
            }
#endregion
            double[,] A = new double[n, n];
            double[] b = new double[n];
            double[] x = new double[n];
            Console.WriteLine("Input matrix:\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    try
                    {
                        A[i, j] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message + "Aborting");
                        Environment.Exit(-10);
                    }
                }
            }
			Console.WriteLine("\nInput vector b :\n");
			for (int i = 0; i < n; i++)
			{
				try
				{
					b[i] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
				}
				catch (Exception ex)
				{
					Console.WriteLine(ex + "Aborting");
					Environment.Exit(-1488);
				}
			}
            Console.WriteLine("Your matrix");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(A[i, j] + "  ");
                }
                Console.Write("\n");

            }
            if (!IsSymmetricalMatrix(A,n))
            {
                Console.WriteLine("Is not symmetrical");
                Environment.Exit(-228);
            }
            Console.WriteLine("\n\n\nMinimal discperancy mehod:\n\n");
            x = MinDiscperancy(A, b, eps);
            Console.WriteLine("Solution vector:\n");
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine(x[i]+"\n");
            }
            Console.WriteLine("Fastest Descent Method:\n");
            x = FastestDescent(A, b, eps);
			Console.WriteLine("Solution vector:\n");
			for (int i = 0; i < n; i++)
			{
				Console.WriteLine(x[i] + "\n");
			}   
        }

        public static double ScalarProduct(double[] a, double[] b)   /*скалярное произведение*/
        {
            double result = .0;
            for (int i = 0; i < a.Length; i++)
            {
                result += a[i] * b[i];
            }
            return result;
        }
        public static double Norm(double[] a, double[] b)
        {
            double sum = 0;
            for (int i = 0; i < a.Length; i++)
            {
                sum += Math.Pow(Math.Abs(a[i] - b[i]), 2.0);
            }
            return Math.Sqrt(sum);
        }
        public static double[] VerticalSum(double[] a, double[] b)
        {
            double[] c = new double[a.Length];
            for (int i = 0; i < a.Length; i++)
            {
                c[i] = a[i] + b[i];
            }
            return c;
        }
        public static double[] VerticalSubstraction(double[] a, double[] b)
        {
            double[] c = new double[a.Length];
            for (int i = 0; i < a.Length; i++)
            {
                c[i] = a[i] - b[i];
            }
            return c;
        }
        public static double[] VectorByNumMultiplication(double a, double[] b)  /*умножение вектора на скаляр*/
                                                                                /*scUmnogV in original Java source*/
        {
            double[] c = new double[b.Length];
            foreach (int i in c)
            {
                c[i] = a * b[i];
            }
            return c;
        }
        public static double[] MatrixByVectorMultiplication(double[,] a, double[] b) /*умножение матрицы на вектор-стобец = вектор столбец*/
                                                                                     /*public double[] mUmnogV in original Java source*/
        {
            double[] c = new double[b.Length];
            for (int i = 0; i < b.Length; i++) /*Заменить на a.Length? Думаю, что не стоит*/
            {
                for (int j = 0; j < b.Length; j++)
                {
                    double[] arrd = c;
                    /*int n2 = i;
					arrd[n2] = arrd[n2] + a[i][j] * b[j];*/
                    arrd[i] = arrd[i] + a[i, j] * b[j];
                    GC.Collect();
                }
            }
            return c;
        }
        public static bool IsSymmetricalMatrix(double[,] a, int size)   //проверят  матрицу на симметричность 
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (!(a[i, j].Equals(a[j, i])))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        public static double[] FastestDescent (double [,] a, double [] b, double eps)   /*Скорейший спуск*/
        {
            double[] x0 = new double[b.Length];
            double[] xk = new double[b.Length];
            double[] xk1 = new double[b.Length];
            double[] rk = new double[b.Length];
            double[] rk1 = new double[b.Length];
            uint iters = 1; /*кол-во итераций*/
            xk1 = x0;
            rk1 = VerticalSubstraction(MatrixByVectorMultiplication(a, x0), b);
            while (Norm(rk1, rk) > eps) 
            {
				rk = rk1;
				xk = xk1;
                double tau = ScalarProduct(rk1, rk1) / ScalarProduct(MatrixByVectorMultiplication(a, rk1), rk1);
                xk1 = VerticalSubstraction(xk, VectorByNumMultiplication(tau, rk));
                rk1 = VerticalSubstraction(rk, VectorByNumMultiplication(tau, MatrixByVectorMultiplication(a, rk)));
                iters++;
            }
            Console.WriteLine("It took " + iters  + " iterations for  fastest descent method ");
            return xk1; 
        }
        public static double [] MinDiscperancy (double [,] a, double [] b, double eps)  /*Минимальная невязка*/
        {
			double[] x0 = new double[b.Length];
			double[] xk = new double[b.Length];
			double[] xk1 = new double[b.Length];
			double[] rk = new double[b.Length];
			double[] rk1 = new double[b.Length];
			uint iters = 1; /*кол-во итераций*/
            xk1 = x0;
            rk1 = VerticalSubstraction(MatrixByVectorMultiplication(a, x0), b);
            while (Norm(rk1,rk) > eps)
            {
				rk = rk1;
				xk = xk1;
                double tau = ScalarProduct(rk1, MatrixByVectorMultiplication(a, rk1)) / ScalarProduct(MatrixByVectorMultiplication(a, rk1), MatrixByVectorMultiplication(a, rk1));
                xk1 = VerticalSubstraction(xk, VectorByNumMultiplication(tau, rk));
                rk1 = VerticalSubstraction(rk, VectorByNumMultiplication(tau, MatrixByVectorMultiplication(a, rk)));
                iters++;
            }
            Console.WriteLine("It took " + iters + " iterations for  Minimal Discperancy method ");
            return xk1;
		}
    }
}
