using System;

namespace SquareRootMethod
{
	class MainClass
	{
		public static void Main(string[] args) /*http://www.scriru.com/14/94179136356.php*/
		{
			Console.BackgroundColor = ConsoleColor.Red;
			Console.ForegroundColor = ConsoleColor.Black;
			Console.WriteLine("Input matrix size");
			int n = 0;
			try
			{
				n = int.Parse(Console.ReadLine());
			}
			catch (Exception ex)
			{
				Console.WriteLine(ex.Message + "\tAbotring");
				Environment.Exit(1);
			}
			double[,] A = new double[n, n];
			double[,] U = new double[n, n];
			double[] b = new double[n];
			double[] x = new double[n];
			double[] y = new double[n];
			double tmp = 0;
			Console.WriteLine("Input matrix A:");
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
						Console.WriteLine(ex.Message + "\tAbotring");
						Environment.Exit(1);
					}
				}
			}
			if (!IsSymmetricalMatrix(A,n))
			{
				Console.WriteLine("Matrix A is NOT symmetrical, aborting");
				Environment.Exit(2);
			}
			Console.WriteLine("Input vector b:");
			for (int i = 0; i < b.Length;i++)
			{
				try
				{
					b[i] = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
				}
				catch (Exception ex)
				{
					Console.WriteLine(ex.Message + "\tAborting");
					Environment.Exit(2);
				}
			}
			for (int i = 0; i < n;i++)
			{
				tmp = 0;
				for (int k = 0; k < i; k++)
				{
					tmp += U[k,i] * U[k,i];
				}
				U[i, i] = Math.Sqrt(A[i, i] - tmp);
				for (int j = i; j < n;j++)
				{
					tmp = 0;
					for (int k = 0; k < i;k++)
					{
						tmp += U[k,i] * U[k,j];
					}
					U[i,j] = (A[i,j] - tmp) / U[i,i];
				}
			}
			Console.WriteLine("Matrix U:");
			for (int i = 0; i < n;i++)
			{
				for (int j = 0; j < n;j++)
				{
					Console.Write(U[i,j]+" ");
				}
				Console.WriteLine();
			}
			for (int i = 0; i < n; i++)
			{
				tmp = 0;
				for (int k = 0; k < i; k++)
				{
					tmp += U[k, i] * y[k];
				}
				y[i] = (b[i] - tmp) / U[i,i];
			}
			for (int i = n - 1; i >= 0; i--)
			{
				tmp = 0;
				for (int k = i + 1; k < n; k++)
				{
					tmp = tmp + U[i,k] * x[k];
				}
				x[i] = (y[i] - tmp) / U[i,i];
			}
			Console.WriteLine("Solution vector:");
			for (int i = 0; i < n;i++)
			{
				Console.WriteLine("X = "+x[i]);
			}
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
	}
}