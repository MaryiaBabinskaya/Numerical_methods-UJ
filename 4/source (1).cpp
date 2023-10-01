//Maryia Babinskaya
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "vectalg.h"
using namespace std;
//Funkcja do rozwiazywania ukladu rownan liniowych metoda eliminacji Gaussa
Vector solveEquations(
        const Matrix & A,   // Macierz (n * n)
        const Vector & b,   // Wektor (n) max n = 3000
        double eps          // dopuszczalny blad
){
    int n = A.size();
    Matrix scaledA = A;
    Vector scaledB = b;
    vector <long double> scaling_factors(n, 0.0);
    for (int i = 0; i < n; i++) {
        double max_val = 0.0;
        for (int j = 0; j < n; j++) {
            max_val = max(max_val, abs(scaledA(i, j)));
        }
        scaling_factors[i] = max_val;
    }
    vector<int> permutations(n);
    for(int i = 0; i < n; i++) permutations[i] = i;
    //Eliminacja Gaussa
    for (int k = 0; k < n - 1; k++){
        long double maxElem = 0.0;
        int maxRow = k;
        for (int i = k; i < n; i++) {
                auto elem = abs(scaledA(permutations[i], k) / scaling_factors[permutations[i]]);
                if (elem > maxElem) {
                    maxElem = elem;
                    maxRow = i;
                }
        }
        swap(permutations[k], permutations[maxRow]);
        for (int i = k + 1; i < n; i++) {
            double factor = scaledA(permutations[i], k) / scaledA(permutations[k], k);
            for (int j = k; j < n; j++) scaledA(permutations[i], j) -= factor * scaledA(permutations[k], j);
            scaledB[permutations[i]] -= factor * scaledB[permutations[k]];
        }
    }
    Vector x(n);
    for (int i = n - 1; i >= 0; i--) {
        long double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += scaledA(permutations[i], j) * x[j];
        }
        x[i] = (scaledB[permutations[i]] - sum) / scaledA(permutations[i], i);
    }
    auto residual = residual_vector(A, b, x);
    if (residual.max_norm() >= eps) {
        auto corrections = solveEquations(A, residual, eps);
        transform(x.begin(), x.end(), corrections.begin(), x.begin(), plus<long double>());
    }
    return x;
}