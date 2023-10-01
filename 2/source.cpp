//Maryia Babinskaya
#include <cmath>
using namespace std;
double findZero(
        double (*f)(double),  // funkcja ktorej zera szukamy w [a, b]
        double a,             // lewy koniec przedzialu
        double b,             // prawy koniec przedzialu
        int M,                // maksymalna dozwolona liczba wywolan funkcji f
        double eps,           // spodziewana dokladnosc zera
        double delta          // wystarczajacy blad bezwzgledny wyniku
){
     double fa = f(a);
     double fb = f(b);
     double c, fc;
     if (abs(fa) < eps) return a;
     if (abs(fb) < eps) return b;
     double sr  = b - a;
    // Bisection method
    //The Bisection method is based on binary slashing and is guaranteed to converge to the root.
    //It does not matter what the function is, the root-error upper bound is fixed at each iteration
    //and can be determined a priori. By specifying the root-error tolerance, the upper bound on the
    //number of iterations can be predetermined quickly.
        while (M > 0) {
            //compute the mid-point
            sr = sr / 2;
            c = a + sr;
            fc = f(c);
            if (abs(fc) < eps) return c;
            else if (abs(sr) < delta) return c;
            else if (abs(sr) < 0.1) break;
            if (fa * fc >= 0) {
                a = c;
                fa = fc;
            } else {
                b = c;
                fb = fc;
            }
            M = M - 1;
        }
    //False Position Method
    while (M > 0) {
        double r = c - fc * (c - a) / (fc - fa);
        double fr = f(r);
        if (abs(fr) < eps) return r;
        if (abs(r-c) < delta) return r;
        a  = c;
        fa = fc;
        c  = r;
        fc = fr;
        M = M - 1;
    }
    return c;
}