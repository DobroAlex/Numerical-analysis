/*
 * Decompiled with CFR 0_123.
 */
import java.applet.Applet;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Label;
import java.awt.LayoutManager;
import java.io.PrintStream;

public class ap2b
extends Applet {
    double[] x = new double[100];
    double[] s1 = new double[100];
    double[] s2 = new double[100];
    double[] h = new double[100];
    double[] temp = new double[100];
    double[] y = new double[]{0.5, 0.8, 0.4, 0.8, 0.5};
    double h1;
    int n = 4;
    public static final int sq = 300;
    public static final double a = -1.0;
    public static final double b = 1.0;
    public static final double xMax = 1.2;
    public static final double yMax = 2.0;
    public static final double xMin = -1.2;
    public static final double yMin = -0.2;
    Label l1 = new Label("\u041a\u0432\u0430\u0434\u0440\u0430\u0442\u0438\u0447\u043d\u044b\u0435 \u043a\u043e\u043d\u0446\u044b", 0);
    Label l2 = new Label("\u0415\u0441\u0442\u0435\u0441\u0442\u0432\u0435\u043d\u043d\u044b\u0439 \u0441\u043f\u043b\u0430\u0439\u043d", 0);

    @Override
    public void init() {
        this.setLayout(null);
        this.l1.setBounds(100, 450, 150, 20);
        this.l2.setBounds(400, 450, 150, 20);
        this.add(this.l1);
        this.add(this.l2);
        this.h1 = 2.0 / (double)this.n;
        int i = 0;
        while (i <= this.n) {
            this.x[i] = -1.0 + (double)i * this.h1;
            this.h[i] = this.h1;
            ++i;
        }
        this.progonka1(this.x, this.y, this.h);
        this.progonka2(this.x, this.y, this.h);
    }

    @Override
    public void paint(Graphics g) {
        double y2;
        double x1;
        double x12;
        double y1;
        Dimension d1 = this.size();
        int x0 = (int)(0.0 + (double)(d1.width - 0) / 2.4 * 1.2);
        int y0 = (int)((double)(d1.height - 50) - (double)(d1.height - 50 - 0) / 2.2 * 0.2);
        this.DrawAxis(g, x0, y0, 0, 0, d1.width, d1.height - 50);
        int j = -10000;
        while (j <= -9000) {
            x1 = 1.0E-4 * (double)j;
            y2 = -0.2;
            this.DrawGraph(g, Color.blue, x0, y0, x1, y2);
            ++j;
        }
        j = 100;
        while (j <= 1100) {
            x1 = 1.0E-4 * (double)j;
            y2 = -0.2;
            this.DrawGraph(g, Color.red, x0, y0, x1, y2);
            ++j;
        }
        int i = 0;
        while (i <= this.n) {
            System.out.println(this.s1[i]);
            ++i;
        }
        i = 0;
        while (i <= this.n) {
            System.out.println(this.s2[i]);
            ++i;
        }
        i = 1;
        while (i <= this.n) {
            int j2 = (int)(this.x[i - 1] * 100000.0);
            while (j2 <= (int)(this.x[i] * 100000.0)) {
                x12 = 1.0E-5 * (double)j2;
                y1 = this.Si(this.x, this.y, this.s1, this.h, i, x12);
                this.DrawGraph(g, Color.blue, x0, y0, x12, y1);
                this.DrawPoint(g, x0, y0, this.x[i - 1], this.y[i - 1]);
                ++j2;
            }
            ++i;
        }
        i = 1;
        while (i <= this.n) {
            int j3 = (int)(this.x[i - 1] * 100000.0);
            while (j3 <= (int)(this.x[i] * 100000.0)) {
                x12 = 1.0E-5 * (double)j3;
                y1 = this.Si(this.x, this.y, this.s2, this.h, i, x12);
                this.DrawGraph(g, Color.red, x0, y0, x12, y1);
                this.DrawPoint(g, x0, y0, this.x[i - 1], this.y[i - 1]);
                ++j3;
            }
            ++i;
        }
        this.DrawPoint(g, x0, y0, this.x[this.n], this.y[this.n]);
    }

    public void form1(double[] a, double[] b, double[] c, double[] f, double[] x, double[] y, double[] h) {
        a[0] = 0.0;
        b[0] = 1.0;
        c[0] = -1.0;
        f[0] = 0.0;
        int i = 1;
        while (i < this.n) {
            a[i] = h[i];
            b[i] = 2.0 * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6.0 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
            ++i;
        }
        a[this.n] = 1.0;
        b[this.n] = -1.0;
        c[this.n] = 0.0;
        f[this.n] = 0.0;
    }

    public void progonka1(double[] x, double[] y, double[] h) {
        double[] a = new double[100];
        double[] b = new double[100];
        double[] c = new double[100];
        double[] f = new double[100];
        double[] p = new double[100];
        double[] q = new double[100];
        this.form1(a, b, c, f, x, y, h);
        int i = 0;
        while (i <= this.n) {
            System.out.println(String.valueOf(a[i]) + "  " + b[i] + "  " + c[i] + "  " + f[i]);
            ++i;
        }
        p[1] = (- c[0]) / b[0];
        q[1] = f[0] / b[0];
        i = 1;
        while (i < this.n) {
            double r = b[i] + a[i] * p[i];
            p[i + 1] = (- c[i]) / r;
            q[i + 1] = (f[i] - a[i] * q[i]) / r;
            ++i;
        }
        this.s1[this.n] = ((- a[this.n]) * q[this.n] + f[this.n]) / (b[this.n] + a[this.n] * p[this.n]);
        i = this.n;
        while (i > 0) {
            this.s1[i - 1] = p[i] * this.s1[i] + q[i];
            --i;
        }
    }

    public void form2(double[] a, double[] b, double[] c, double[] f, double[] x, double[] y, double[] h) {
        a[1] = 0.0;
        b[1] = 2.0 * (h[1] + h[2]);
        c[1] = h[2];
        f[1] = 6.0 * ((y[2] - y[1]) / h[2] - (y[1] - y[0]) / h[1]);
        int i = 2;
        while (i < this.n - 1) {
            a[i] = h[i];
            b[i] = 2.0 * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6.0 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
            ++i;
        }
        a[this.n - 1] = h[this.n - 1];
        b[this.n - 1] = 2.0 * (h[this.n - 1] + h[this.n]);
        c[this.n - 1] = 0.0;
        f[this.n - 1] = 6.0 * ((y[this.n] - y[this.n - 1]) / h[this.n] - (y[this.n - 1] - y[this.n - 2]) / h[this.n - 1]);
    }

    public void progonka2(double[] x, double[] y, double[] h) {
        double[] a = new double[100];
        double[] b = new double[100];
        double[] c = new double[100];
        double[] f = new double[100];
        double[] p = new double[100];
        double[] q = new double[100];
        this.form2(a, b, c, f, x, y, h);
        int i = 0;
        while (i <= this.n) {
            System.out.println(String.valueOf(a[i]) + "  " + b[i] + "  " + c[i] + "  " + f[i]);
            ++i;
        }
        p[2] = (- c[1]) / b[1];
        q[2] = f[1] / b[1];
        i = 2;
        while (i < this.n - 1) {
            double r = b[i] + a[i] * p[i];
            p[i + 1] = (- c[i]) / r;
            q[i + 1] = (f[i] - a[i] * q[i]) / r;
            ++i;
        }
        this.s2[this.n] = 0.0;
        this.s2[this.n - 1] = ((- a[this.n - 1]) * q[this.n - 1] + f[this.n - 1]) / (b[this.n - 1] + a[this.n - 1] * p[this.n - 1]);
        i = this.n - 1;
        while (i > 0) {
            this.s2[i - 1] = p[i] * this.s2[i] + q[i];
            --i;
        }
        this.s2[0] = 0.0;
    }

    public double Si(double[] x, double[] y, double[] s, double[] h, int i, double xx) {
        return (s[i - 1] * Math.pow(x[i] - xx, 3.0) + s[i] * Math.pow(xx - x[i - 1], 3.0) + (xx - x[i - 1]) * (6.0 * y[i] - Math.pow(h[i], 2.0) * s[i]) + (x[i] - xx) * (6.0 * y[i - 1] - Math.pow(h[i], 2.0) * s[i - 1])) / (6.0 * h[i]);
    }

    public void DrawAxis(Graphics g, int x, int y, int ex1, int ey1, int ex2, int ey2) {
        int i = 0;
        g.setColor(Color.black);
        g.drawLine(ex1, y, ex1 + ex2, y);
        g.drawLine(ex1 + ex2, y, ex1 + ex2 - 20, y - 10);
        g.drawLine(ex1 + ex2, y, ex1 + ex2 - 20, y + 10);
        while (ex1 + x + i * 300 < ex1 + ex2) {
            g.drawLine(x + i * 300, y - 4, x + ++i * 300, y + 4);
            this.DrawString(g, Color.black, 1, 14, x + i * 300 - 4, y + 18, "" + i);
            g.drawLine(x - i * 300, y - 4, x - i * 300, y + 4);
            this.DrawString(g, Color.black, 1, 14, x - i * 300 - 8, y + 18, "-" + i);
        }
        g.drawLine(x, ey1, x, ey2);
        g.drawLine(x, ey1, x - 10, ey1 + 20);
        g.drawLine(x, ey1, x + 10, ey1 + 20);
        i = 0;
        while (y - i * 300 > ey1) {
            g.drawLine(x - 4, y - i * 300, x + 4, y - ++i * 300);
            this.DrawString(g, Color.black, 1, 14, x - 15, y + i * 300 + 4, "-" + i);
            g.drawLine(x - 4, y + i * 300, x + 4, y + i * 300);
            this.DrawString(g, Color.black, 1, 14, x - 15, y - i * 300 + 4, "" + i);
        }
        this.DrawString(g, Color.black, 1, 14, ex2 - 15, y - 15, "X");
        this.DrawString(g, Color.black, 1, 14, x - 15, 15, "Y");
    }

    public void DrawPoint(Graphics g, int x0, int y0, double x, double y) {
        g.setColor(Color.black);
        int xx = (int)((double)x0 + x * 300.0);
        int yy = (int)((double)y0 - y * 300.0);
        g.fillOval(xx - 3, yy - 3, 6, 6);
    }

    public void DrawGraph(Graphics g, Color col, int x0, int y0, double x, double y) {
        g.setColor(col);
        int xx = (int)((double)x0 + x * 300.0);
        int yy = (int)((double)y0 - y * 300.0);
        g.drawOval(xx, yy, 1, 1);
    }

    public void DrawString(Graphics g, Color col, int u, int v, int x, int y, String s) {
        g.setColor(col);
        Font f = new Font("Helvetica", u, v);
        g.setFont(f);
        g.drawString(s, x, y);
    }

    public void DrawString1(Graphics g, Color col, int u, int v, int x0, int y0, double x, double y, String s) {
        g.setColor(col);
        Font f = new Font("Helvetica", u, v);
        g.setFont(f);
        int xx = (int)((double)x0 + x * 300.0);
        int yy = (int)((double)y0 - y * 300.0);
        g.drawString(s, xx, yy);
    }

    int StrToInt(String S) {
        Integer I = new Integer(S);
        return I;
    }
}
