using System;

namespace Lab7Task1
{
	class MainClass
	{
		public static void Main (string[] args)
		{

		}
	}
	public static  class GaussianSolver
	{
		public static double formatDouble(double d, int dz) {
			double dd = Math.Pow(10.0, dz);
			return (double)Math.Round(d * dd) / dd;
		}
		public static double[] gauss(double[,] m, int n) {
			GaussianSolver.direct(m, n);
			return GaussianSolver.reverse(m, n);
		}
		public static double[] reverse(double[,] m, int n) {
			double[] q = new double[n];
			q[n - 1] = m[n - 1,n] / m[n - 1, n - 1];
			int i = n - 2;
			while (i >= 0) {
				double sum = m[i,n];
				int k = i + 1;
				while (k < n) {
					sum -= m[i, k] * q[k];
					++k;
				}
				q[i] = sum / m[i, i];
				--i;
			}
			return q; 
		}
		public static double findMain(double[,] m, int n, int i) {
			double[] temp = new double[n + 1];
			int l = i;
			int k = i;
			while (k < n) {
				if (Math.Abs(m[l,i]) < Math.Abs(m[k,i])) {
					l = k;
				}
				++k;
			}
			if (l != i) {
				k = 0;
				while (k <= n) {
					temp[k] = m[l,k];
					m[l,k] = m[i,k];
					m[i,k] = temp[k];
					++k;
				}
			}
			return m[l,i];
		}
		public static void direct(double[,] m, int n) {
			int i = 0;
			while (i < n) {
				GaussianSolver.findMain(m, n, i);
				if (m[i,i] == 0.0) break;
				int k = i + 1;
				while (k < n) {
					double d = m[k,i] / m[i,i];
					int j = i;
					while (j <= n) {
						m[k,j] = m[k,j] - d * m[i,j];
						++j;
					}
					++k;
				}
				//this.print(i + 1, this.formatDouble(this.findmain(m, n, i), 2), m, n);
				++i;
			}
		}
		public static int rank(double[,] m, int n)
		{
			double[,] r = new double[n, n + 1];
			int b = 0;
			while (b < n) {
				int h = 0;
				while (h < n + 1) {
					r[b,h] = m[b,h];
					++h;
				}
				++b;
			}
			int i = 0;
			while (i < n) {
				GaussianSolver.findMain(r, n, i);
				if (r[i,i] == 0.0) break;
				int j = i + 1;
				while (j < n) {
					double d = r[j,i] / r[i,i];
					int k = i;
					while (k <= n) {
						r[j,k] = r[j,k] - d * r[i,k];
						++k;
					}
					++j;
				}
				++i;
			}
			int rang = 0;
			int i2 = 0;
			while (i2 < n) {
				int k = 0;
				int j = 0;
				while (j < n) {
					if (r[i2,j] == 0.0) {
						++k;
					}
					++j;
				}
				if (k != n) {
					++rang;
				}
				++i2;
			}
			return rang;
		}

	}
}
