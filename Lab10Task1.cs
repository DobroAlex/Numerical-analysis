using System;

namespace Lab10Task1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            double a = -100;
            double b =  100;
            double p = 0;
            double eps = 0;
            Console.WriteLine("Input p:");
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

            Console.WriteLine("x = " + Dixotomy(a, b, eps, p));
        }
		public static double Func(double x, double p)
		{
            return Math.Pow(0.5,x)-p*x;
		}
        static double Dixotomy (double a,double b, double eps, double p) /*https://studlearn.com/works/details/reshenie-uravneniy-metodom-bisektsii-polovinn-712*/
		{
            double c = (a + b) / 2.0;
            if (Func(a,p) * Func(c,p) <0 )
            {
                b = c;
            }
            else
            {
                a = c;
            }
            if (Math.Abs(b - a) > eps && !(Func(c, p).Equals(0.0))) 
            {
                return Dixotomy(a, b, eps, p);
            }
            else
            {
                return c;
            }
        }
    }

}
