using System;

namespace ChordsMethod
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            decimal a=0, b=0, eps=0;
            Console.WriteLine("Input a,b, eps in separate lines \n!!!!!!(|a| != |b|)!!!!!");
            try
            {
                a = decimal.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
                b = decimal.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
                eps = decimal.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message+ex.StackTrace+"Aborting");
                Environment.Exit(-1);
            }
            Console.WriteLine("Now solving 2x^2 - 3 = 0");
            Console.WriteLine("x=" + ChordsMethod.MainClass.FindRoot(a, b, eps));
        }
        public static decimal func (decimal x)
        {
            return 2.0M*x*x-5.0M;
        }
        public static decimal FindRoot(decimal a, decimal b, decimal eps) //метод хорд
        {
            while (Math.Abs(b-a) >eps)
            checked
            {

				a = b - (b - a) * func(b) / (func(b) - func(a));
				b = a + (a - b) * func(a) / (func(a) - func(b));
            }
            return b;
        }
    }
}
