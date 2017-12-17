using System;

namespace lab6 {

	class MainClass {

        public static float Rectangle(PointsTuple pt) {
            int n = pt.x.Length;
            float h = pt.x[1] - pt.x[0];
            float sum = 0;
            for (int i = 0; i < n - 1; i++) {
                sum += (pt.y[i + 1] + pt.y[i]) / 2;
            }
            return h * sum;
        }

        public static float Trapeze(PointsTuple pt) {
            int n = pt.x.Length;
            float h = pt.x[1] - pt.x[0];
            float sum = 0;
            for (int i = 1; i < n - 1; i++) {
                sum += pt.y[i];
            }
            return (h / 2) * (pt.y[0] + 2 * sum + pt.y[n - 1]);
        }

        public static float Simpson(PointsTuple pt) {
			int n = pt.x.Length;
			int k = n / 2;
			float h = pt.x[1] - pt.x[0];

			float oddsum = 0, evensum = 0;
			for (int i = 1; i <= k; i++) {
				oddsum += pt.y[2 * i - 1];
			}
			for (int i = 1; i <= k - 1; i++) {
				oddsum += pt.y[2 * i];
			}
			return h / 3.0f * (pt.y[0] + 4 * oddsum + 2 * evensum + pt.y[n - 1]);
		}

        public static float NewtonKotess(PointsTuple pt) {
            int n = pt.x.Length;
            float range = pt.x[n - 1] - pt.x[0];
            float sum = 0;
            for (int i = 0; i < n; i++) {
                sum += NewtonKotessCoef[n - 1][i] * pt.y[i];
            }
            return range * sum;
        }

        /// <summary>
        /// Returns result of integral or null, if error occurs
        /// </summary>
        public static float? TrySolveIntegral(Func<PointsTuple, float> method, PointsTuple pt) {
            try {
                return method(pt);
            } catch (Exception) {
                return null;
            }
        }

        /// <summary>
        /// Struct that contains web values of some function
        /// </summary>
        public struct PointsTuple {
            public float[] x { get; }
            public float[] y { get; }

            public PointsTuple(float[] x, float[] y) {
                if (x.Length != y.Length || x.Length == 0) {
                    throw new FormatException();
                }
                this.x = x;
                this.y = y;
            }

            public override string ToString() {
                string[] result = new string[x.Length];
                for (int i = 0; i < x.Length; i++) {
                    result[i] = "[" + x[i] + " " + y[i] + "]";
                }
                return String.Join(", ", result);
            }
        }

        /// <summary>
        /// Returns optimal step for given epslon
        /// </summary>
        /*public static float GetStepByEpsilon(float M, int p, float A, float a, float b, float epsilon) {
            return (float)Math.Pow((A * epsilon) / ((b - a ) * M), (1.0 / p));
        }*/

        /// <summary>
        /// Convert step to power of two, but lesser then given step
        /// </summary>
        /*public static float MakeStepLessThenPowerOfTwo(float raw) {
            float nice = 1;
            if (raw < 1) {
                while (nice > raw) {
                    nice /= 2;
                }
            } else if (raw > 1) {
                while (nice < raw) {
                    nice *= 2;
                }
                nice /= 2;
            }
            return nice;
        }*/

        /// <summary>
        /// Generates tuple of points by given function, range and step
        /// </summary>
        public static PointsTuple GetPointTupleByStep(Func<float, float> function, float step, float from, float to) {
            int n = (int)Math.Ceiling((to - from) / step);
            float[] x = new float[n + 1];
            float[] y = new float[n + 1];
            float progress = from;
            for (int i = 0; i <= n; i++) {
                x[i] = progress;
                y[i] = function(progress);
                if (float.IsNaN(y[0])) {
                    y[i] = 0;
                }
                progress += step;
            }
            return new PointsTuple(x, y);
        }

        public static float[][] NewtonKotessCoef = new float[][] {
            null,
            new float[] { .5f , .5f },
            new float[] { .166f, 0.666f, .166f },
            new float[] { .125f, .375f, .375f, .125f },
            null,
            new float[] { .065f, .26f, .173f, .173f, .26f, .065f },
        };

        

        public static void Main (string[] args) {

            //1-1
            float alpha = 1.5f;
            PointsTuple sinAXbyX = GetPointTupleByStep((x) => (float)Math.Sin(alpha * x) / x, 0.01f, 0, 1);
            //Console.WriteLine("Points:" + sinAXbyX);
            Console.WriteLine("1-1, Rectangle: " + TrySolveIntegral(Rectangle, sinAXbyX) + "\n");

            //2-4
            PointsTuple lobachevski = GetPointTupleByStep((x) => -(float)Math.Log(Math.Cos(x)), 0.01f, 0, (float)(Math.PI / 3));
            //Console.WriteLine("Points:" + lobachevski);
            Console.WriteLine("2-4, Rectangle: " + TrySolveIntegral(Rectangle, lobachevski) + "\n");

            //3
            PointsTuple cosXbyXplus1 = GetPointTupleByStep((x) => (float)Math.Cos(x) / (1 + x), 0.2f, 0, 1);
            Console.WriteLine("Points:" + cosXbyXplus1);
            Console.WriteLine("3, Rectangle: " + TrySolveIntegral(Rectangle, cosXbyXplus1));
            Console.WriteLine("3, Newton-Kotess: " + TrySolveIntegral(NewtonKotess, cosXbyXplus1));

            while (Console.ReadKey(true).Key != ConsoleKey.Enter) { }
        }
	}
}
