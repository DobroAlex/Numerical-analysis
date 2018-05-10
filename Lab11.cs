/*Рунге-Кутты 4 порядка точности*/
using System;

namespace Lab11
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Input segment [x0,X]:");
            int x0 = int.Parse(Console.ReadLine());
            int X = int.Parse(Console.ReadLine());
            Console.WriteLine("Initial condition y(" + x0 + ")= :");
            double y0 = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            Console.WriteLine("Input step h:");
            double h = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            int n = (int)(Math.Abs(X - x0) / h);
            Console.WriteLine("n=" + n);
            double yi = y0;
            double xi = x0;

            for(int i = 0;i<=n;i++)
            {
                Console.WriteLine("Step "+i+"\nYi="+yi+"\tXi="+xi);
                double k1 = h * Func(xi, yi);
                double k2 = h * Func(xi + h / 3, yi +k1/3);
                double k3 = h * Func(xi + 2 * h / 3, yi + k1 / 3 + k2);
                double k4 = h * Func(xi + h, yi + k1 - k2 + k3);
                double deltay = (k1 + 3 * k2 + 3 * k3 + k4) / 8;
                yi += deltay;
                xi += h;
                Console.WriteLine("k1="+k1+"\tk2="+k2+"\tk3="+k3+"\tk4="+k4+"\tdeltaY="+deltay);
            }
            Console.WriteLine("Answer is Y="+yi);
        }
        public static double Func(double x, double y)
        {
            //return 2.0 * Math.Exp(-x) + x - 1.0;
            return x - y;
        }
    }
}
