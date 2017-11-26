/*
 * Decompiled with CFR 0_123.
 */
import java.applet.Applet;
import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.LayoutManager;
import java.awt.TextField;
import java.io.PrintStream;

public class ap1d
extends Applet {
    double[] h = new double[100];
    double[] s = new double[100];
    double[] x = new double[]{-2.0, -1.0, 0.0, 1.0, 2.0};
    double[] y = new double[]{0.0, 0.7, 1.0, 0.7, 0.0};
    double s1 = 0.0;
    double s2 = -10.0;
    int n = 4;
    public static final int sq = 150;
    public static final double xMax = 2.5;
    public static final double yMax = 2.0;
    public static final double xMin = -2.5;
    public static final double yMin = -0.5;
    GridLayout g = new GridLayout(3, 2);
    Label l1 = new Label("f'(x0):", 1);
    TextField tx1 = new TextField(3);
    Label l2 = new Label("f'(xn):", 1);
    TextField tx2 = new TextField(3);
    Button b1 = new Button("Ok");

    @Override
    public void init() {
        this.setLayout(null);
        this.l1.setBounds(20, 20, 40, 20);
        this.tx1.setBounds(70, 20, 50, 20);
        this.l2.setBounds(20, 50, 40, 20);
        this.tx2.setBounds(70, 50, 50, 20);
        this.b1.setBounds(20, 80, 40, 20);
        this.add(this.l1);
        this.add(this.l2);
        this.add(this.tx1);
        this.add(this.tx2);
        this.add(this.b1);
        this.tx1.setText(Double.toString(this.s1));
        this.tx2.setText(Double.toString(this.s2));
        int i = 1;
        while (i <= this.n) {
            this.h[i] = this.x[i] - this.x[i - 1];
            ++i;
        }
        this.progonka(this.x, this.y, this.h, this.s1, this.s2);
    }

    @Override
    public void paint(Graphics g) {
        Dimension d1 = this.size();
        int x0 = (int)(0.0 + (double)(d1.width - 0) / 5.0 * 2.5);
        int y0 = (int)((double)d1.height - (double)(d1.height - 0) / 2.5 * 0.5);
        this.DrawAxis(g, x0, y0, 0, 0, d1.width, d1.height);
        int i = 0;
        while (i <= this.n) {
            System.out.println(this.s[i]);
            ++i;
        }
        i = 0;
        while (i <= this.n) {
            this.DrawPoint(g, x0, y0, this.x[i], this.y[i]);
            ++i;
        }
        i = 1;
        while (i <= this.n) {
            int j = (int)(this.x[i - 1] * 10000.0);
            while (j <= (int)(this.x[i] * 10000.0)) {
                double x1 = 1.0E-4 * (double)j;
                double y1 = this.Si(this.x, this.y, this.s, this.h, i, x1);
                this.DrawGraph(g, Color.blue, x0, y0, x1, y1);
                this.DrawPoint(g, x0, y0, this.x[i - 1], this.y[i - 1]);
                ++j;
            }
            ++i;
        }
        this.DrawPoint(g, x0, y0, this.x[this.n], this.y[this.n]);
    }

    @Override
    public boolean action(Event e, Object arg) {
        if (e.target == this.b1) {
            this.s1 = this.StrToDouble(this.tx1.getText());
            this.s2 = this.StrToDouble(this.tx2.getText());
            this.progonka(this.x, this.y, this.h, this.s1, this.s2);
            this.repaint();
            return true;
        }
        return false;
    }

    public void form(double[] a, double[] b, double[] c, double[] f, double[] x, double[] y, double[] h, double s1, double s2) {
        a[0] = 0.0;
        b[0] = 2.0;
        c[0] = 1.0;
        f[0] = 6.0 * ((y[1] - y[0]) / Math.pow(h[1], 2.0) - s1 / Math.pow(h[1], 2.0));
        int i = 1;
        while (i < this.n) {
            a[i] = h[i];
            b[i] = 2.0 * (h[i] + h[i + 1]);
            c[i] = h[i + 1];
            f[i] = 6.0 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
            ++i;
        }
        a[this.n] = 1.0;
        b[this.n] = 2.0;
        c[this.n] = 0.0;
        f[this.n] = -6.0 * ((y[this.n] - y[this.n - 1]) / Math.pow(h[this.n], 2.0) - s2 / Math.pow(h[this.n], 2.0));
    }

    public void progonka(double[] x, double[] y, double[] h, double s1, double s2) {
        double[] a = new double[100];
        double[] b = new double[100];
        double[] c = new double[100];
        double[] f = new double[100];
        double[] p = new double[100];
        double[] q = new double[100];
        this.form(a, b, c, f, x, y, h, s1, s2);
        int i = 0;
        while (i <= this.n) {
            System.out.println(String.valueOf(a[i]) + "   " + b[i] + "    " + c[i] + "   " + f[i]);
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
        this.s[this.n] = ((- a[this.n]) * q[this.n] + f[this.n]) / (b[this.n] + a[this.n] * p[this.n]);
        i = this.n;
        while (i > 0) {
            this.s[i - 1] = p[i] * this.s[i] + q[i];
            --i;
        }
    }

    public double Si(double[] x, double[] y, double[] s, double[] h, int i, double xx) {
        return (s[i - 1] * Math.pow(x[i] - xx, 3.0) + s[i] * Math.pow(xx - x[i - 1], 3.0) + (xx - x[i - 1]) * (6.0 * y[i] - h[i] * h[i] * s[i]) + (x[i] - xx) * (6.0 * y[i - 1] - h[i] * h[i] * s[i - 1])) / (6.0 * h[i]);
    }

    public void DrawAxis(Graphics g, int x, int y, int ex1, int ey1, int ex2, int ey2) {
        int i = 0;
        g.setColor(Color.black);
        g.drawLine(ex1, y, ex1 + ex2, y);
        g.drawLine(ex1 + ex2, y, ex1 + ex2 - 20, y - 10);
        g.drawLine(ex1 + ex2, y, ex1 + ex2 - 20, y + 10);
        while (ex1 + x + i * 150 < ex1 + ex2) {
            g.drawLine(x + i * 150, y - 4, x + ++i * 150, y + 4);
            this.DrawString(g, Color.black, 1, 14, x + i * 150 - 4, y + 18, "" + i);
            g.drawLine(x - i * 150, y - 4, x - i * 150, y + 4);
            this.DrawString(g, Color.black, 1, 14, x - i * 150 - 8, y + 18, "-" + i);
        }
        g.drawLine(x, ey1, x, ey2);
        g.drawLine(x, ey1, x - 10, ey1 + 20);
        g.drawLine(x, ey1, x + 10, ey1 + 20);
        i = 0;
        while (y - i * 150 > ey1) {
            g.drawLine(x - 4, y - i * 150, x + 4, y - ++i * 150);
            this.DrawString(g, Color.black, 1, 14, x - 15, y + i * 150 + 4, "-" + i);
            g.drawLine(x - 4, y + i * 150, x + 4, y + i * 150);
            this.DrawString(g, Color.black, 1, 14, x - 15, y - i * 150 + 4, "" + i);
        }
        this.DrawString(g, Color.black, 1, 14, ex2 - 15, y - 15, "X");
        this.DrawString(g, Color.black, 1, 14, x - 15, 15, "Y");
    }

    public void DrawPoint(Graphics g, int x0, int y0, double x, double y) {
        g.setColor(Color.black);
        int xx = (int)((double)x0 + x * 150.0);
        int yy = (int)((double)y0 - y * 150.0);
        g.fillOval(xx - 3, yy - 3, 6, 6);
    }

    public void DrawGraph(Graphics g, Color col, int x0, int y0, double x, double y) {
        g.setColor(col);
        int xx = (int)((double)x0 + x * 150.0);
        int yy = (int)((double)y0 - y * 150.0);
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
        int xx = (int)((double)x0 + x * 150.0);
        int yy = (int)((double)y0 - y * 150.0);
        g.drawString(s, xx, yy);
    }

    double StrToDouble(String S) {
        Double D = new Double(S);
        return D;
    }

    int StrToInt(String S) {
        Integer I = new Integer(S);
        return I;
    }
}
