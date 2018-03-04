using System;

namespace Lab8Task1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Input calcuation accuracy :");
            double EPS = Double.Parse(Console.ReadLine());
            Console.Write(EPS);
            int n = 0;
            Console.WriteLine("Input square matrix size :");
            try
            {
                n = int.Parse(Console.ReadLine());
                if (n <= 0 || EPS <= 0 || EPS < double.Epsilon)
                {
                    throw new System.ArgumentException("size or accuracy  can't be  <= 0");
                }
            }
            catch (ArgumentNullException)
            {
                Console.WriteLine("\nSize or accuracy is  null");
                Environment.Exit(-1);
            }
            catch (FormatException)
            {
                Console.WriteLine("\nWrong input format");
                Environment.Exit(-2);
            }
            catch (OverflowException)
            {
                Console.WriteLine("\nValue is TOO big (Like my dick ;-])");
                Environment.Exit(-3);
            }
            catch (ArgumentException)
            {
                Console.WriteLine("size or accuracy  can't be  <= 0");
                Environment.Exit(-4);
            }
            double[,] A = new double[n, n];
            double[] B = new double[n];
            double[,] C = new double[n, n];
            double[] D = new double[n];
            double[] Xk1 = new double[n];
            Console.WriteLine("Input matrix A :\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {

                    A[i, j] = Double.Parse(Console.ReadLine());
                }
            }
            Console.WriteLine("Your matrix A:\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(A[i, j]);
                    Console.Write(' ');
                }
                Console.Write('\n');
            }
            Console.WriteLine("\nInput vector (right) B:\n");
            for (int i = 0; i < B.Length; i++)
            {
                B[i] = double.Parse(Console.ReadLine());
            }
            Console.WriteLine("\nYour vector B:\n");
            for (int i = 0; i < B.Length; i++)
            {
                Console.Write(B[i]);
                Console.Write('\n');
            }
            if (IsDiagonaleDominate(A, n))
            {
                Console.WriteLine("The condition of diagonal dominance is fulfilled.\nCalculating matrix C:\n");
                C = FormMatrixC(A, n);
                D = FormVectorD(A, B);
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        Console.Write(A[i,j]);
                        Console.Write('\t');
                    }
                    Console.Write('\n');
                }
                Console.WriteLine("vector D:\n");
                for (int i = 0; i < D.Length;i++)
                {
                    Console.Write(D[i]);
                    Console.Write('\n');
                }
                Xk1 = SimpleIteration(C, D, EPS);
                for (int i = 0; i < Xk1.Length;i++)
                {
                    Console.Write(Xk1[i]);
                    Console.Write(' ');                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
                }
            }
            else 
            {
                Console.WriteLine("The condition of diagonal dominance is NOT fulfilled, Aborting");
            }
        }
        public  static double [] SimpleIteration (double [,] c, double [] d,  double eps)
        {
            double[] xk = new double[d.Length];
            xk[d.Length - 1] = 1.0;
            double[] xk1 = new double[d.Length];
            xk1 = VertSum(FormSomeRealShit(c, xk ), d);
            int iters = 1;
            while (Norma(xk1,xk) > eps)
            {
                xk = xk1;
                xk1 = VertSum(FormSomeRealShit(c, xk), d);
                iters++;
            }
            Console.WriteLine("\nIt took ");
            Console.Write(iters);
            Console.WriteLine(" iterations\n.");
            return xk1;
        }
        public static double[] VertSum(double[] a, double[] b)
        {
            double[] c = new double[a.Length];
            for (int i = 0; i < a.Length; i++)
            {
                c[i] = a[i] + b[i];
            }
            return c;
        }
        public static bool IsDiagonaleDominate(double[,] A, int n) //проверка на диагональное преобладание, всё по заветам методички Косовой <3
        {
            int c = 0;
            for (int i = 0; i < n; i++)
            {
                double sum = .0;
                for (int j = 0; j < n; j++)
                {
                    if (i != j)
                    {
                        sum += Math.Abs(A[i, j]);
                    }
                }
                if (Math.Abs(A[i, i]) > sum)
                {
                    c++;
                }

            }
            if (c == n)
            {
                return true;
            }
            return false;
        }
        public static double Norma(double[] a, double[] b) //вычисление нормы, очевидно
        {
            double sum = .0;
            for (int i = 0; i < a.Length; i++)
            {
                sum += Math.Pow(Math.Abs(a[i] - b[i]), 2.0); // модуль разности в квадрате
            }
            return Math.Sqrt(sum);
        }
        public static double[,] FormMatrixC(double[,] A, int n) //создание матрицы C
        {
            double[,] m = new double[n, n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    m[i, j] = i == j ? 0.0 : (-A[i, j]) / A[i, i];
                }
            }
            return m;
        }
        public static double[] FormVectorD(double[,] A, double[] b)
        {
            double[] v = new double[b.Length];
            for (int i = 0; i < b.Length;i++)
            {
                v[i] = b[i] / A[i, i]; //эл-ты с главной диагонали м-цы 
            }
            return v;
        }
        public static double [  ] FormSomeRealShit(double [,] A, double [] b) //mumnogv в оригинальных сырцах. Пока не улавливаю
        {
            double[] c = new double[b.Length];
            for (int i = 0; i < b.Length; i++)
            {
                for (int j = 0; j < b.Length; j++)
                {
                    double[] arrD = c; // arrD теперь хранит указатель на с. Разобраться, нужно это или скопировать независимое значение
                    arrD[i] = arrD[i] + A[i, j] * b[j];
                }
            }
            return c;
        }
    }
}

