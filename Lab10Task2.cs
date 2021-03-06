﻿using System;
/*https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%9D%D1%8C%D1%8E%D1%82%D0%BE%D0%BD%D0%B0*/
namespace Lab10Task2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Input p:");
            double p = 0.0, eps = 0.0, xk = 0.0;
            try
            {
                p = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + "Aborting");
                Environment.Exit(-1);
            }
            Console.WriteLine("Input calculation accuracy:");
            try
            {
                eps = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + "Aborting");
                Environment.Exit(-1);
            }
            Console.WriteLine("Input Xk:");
            try
            {
                xk = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message + "Aborting");
                Environment.Exit(-1);
            }
            Console.WriteLine(SolveViaTantgentsMethod(xk, p, eps));

        }
        public static double SolveViaTantgentsMethod(double x0, double p, double eps)
        {
            double x1 = x0 - f(x0, p) / df(x0, p);
            while (Math.Abs(x1 - x0) > eps)
            {
                x0 = x1;
                x1 = x1 - f(x1, p) / df(x1, p);
            }
            return x1;
        }

        public static double f(double x, double p)/*сама ф-ция*/
        {

            return Math.Cos(x) - p * x;
        }
        public static double df(double x, double p)/*первая производная*/
        {

            return -p - Math.Sin(x);
        }
        public static double df2(double x, double p)/*Вторая производная*/
        {

            return -Math.Cos(x);
        }


    }
}
