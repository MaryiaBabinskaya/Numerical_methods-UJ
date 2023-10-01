//Maryia Babinskaya
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
void printVector(const double* x, unsigned N){
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}
typedef void (*FuncPointer)(const double* x, double* y, double* Df);
int findCurve(FuncPointer f, double* x, unsigned k, double h) {
    double y[2];  //wartosc funkcji w punkcie (a, b) dla danego c
    double Df[2 * 3]; //pochodne czastkowe funkcji w punkcie (a, b) dla danego c
    int error_index = 0;
    for (unsigned i = 0; i < k; i++) {
        x[2] = h + x[2];
        //Implementacja metody Newtona
        double max_error = 0.0;
        for (int iter = 0; iter < 100; iter++) {
            f(x, y, Df); //wywolanie funkcji f w punkcie (a, b) dla danego c, obliczenie wartosci funkcji y oraz pochodnych Df
            double det = Df[0] * Df[4] - Df[1] * Df[3]; //wyznacznik macierzy Jacobiego
            if (det == 0.0) {
                error_index = i + 1; //ustawienie indeksu bledu na aktualny indeks iteracji
                break;
            }
            //obliczenie przyrostow (a, b) na podstawie pochodnych Df i wartosci funkcji y
            x[0] -= (Df[4] * y[0] - Df[1] * y[1]) / det; //aktualizacja a
            x[1] -= (-Df[3] * y[0] + Df[0] * y[1]) / det; //aktualizacja b
            f(x, y, Df); //wywolanie funkcji f w zaktualizowanym punkcie (a, b), obliczenie wartosci funkcji y oraz pochodnych Df
            max_error = fmax(fabs(y[0]), fabs(y[1])); //obliczenie maksymalnego bledu na podstawie wartosci funkcji y
            if (max_error < 1e-14) break;
        }
        if (max_error >= 1e-14) {
            error_index = i + 1;
            break;
        }
        printVector(x, 3);
    }
    return error_index;
}
int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {
    double y[1];
    double Df[1 * 3];
    double a = x[2];
    for (unsigned i = 1; i <= k1; ++i) {
        x[1] = h1 + x[1];
        x[2] = a;
        for (unsigned j = 1; j <= k2; ++j) {
            x[2] = h2 + x[2];
            for (unsigned m = 0; m < 100; m++) {
                f(x, y, Df);
                if (abs(y[0]) <= 1e-14) break;
                double det = Df[0];
                if (abs(det) < 1e-14) {
                    return (i + 1) * k1 + (j + 1);
                }
                x[0] -= y[0] / det;
            }
            printVector(x, 3);
        }
        cout << endl;
    }
    return 0;
}
int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2) {
    double y[2];
    double Df[2 * 4];
    double a = x[3];
    int error_index = 0;
    double maxNorm;
    for (unsigned i = 0; i < k1; ++i) {
        x[2] = x[2] + h1;
        x[3] = a;
        for (unsigned j = 0; j < k2; ++j) {
            x[3] = x[3] + h2;
            for (int iter = 0; iter < 100; iter++) {
                f(x, y, Df);
                // Solve linear system Df*dx = y
                Df[0] -= 1;
                Df[5] -= 1;
                double det = Df[0] * Df[5] - Df[1] * Df[4];
                if (abs(det) < 1e-14) return (i + 1) * k1 + (j + 1);
                // Check if f(x) is close to (x, y) in maximum norm
                maxNorm = abs(y[0] - x[0]);
                maxNorm = max(maxNorm, abs(y[1] - x[1]));
                if (maxNorm <= 1e-14) break;
                double Y[2];
                Y[0] = y[0] - x[0];
                Y[1] = y[1] - x[1];
                if (fabs(Y[0]) <= 1e-14 && fabs(Y[1]) <= 1e-14) {
                    error_index = j + 1;
                    break;
                }
                x[0] -= (Df[5] * Y[0] - Df[1] * Y[1]) / det; //aktualizacja a
                x[1] -= (-Df[4] * Y[0] + Df[0] * Y[1]) / det; //aktualizacja b
            }
            printVector(x, 4);
        }
        cout << endl;
    }
    return error_index;
}