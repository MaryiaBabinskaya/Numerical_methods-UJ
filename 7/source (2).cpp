//Maryia Babinskaya
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
long factorial(unsigned int n) {
    if (n == 0 || n == 1) return 1;
    else return n * factorial(n - 1);
}
vector<long double> WSPinterpolacja(vector<long double>& X, vector<long double>& Y){
    int n = Y.size();
    vector<long double> W(n), f1(n), f2(n);
    int iter = 0;
    f1[0] = Y[0];
    f2[0] = iter;
    for (int i = 0; i < X.size() - 1; i++) {
        if (X[i] != X[i + 1]) iter = i + 1; //if nie powtorzaja sie
        f1[i + 1] = Y[iter];
        f2[i + 1] = iter;
    }
    for (int i = 0; i < X.size(); i++) {
        for (int j = 0; j < f1.size() - i; j++) {
            if (X[j] == X[j + i]) f1[j] = Y[f2[j] + i] / factorial(i); //if powtorka
            else f1[j] = (f1[j + 1] - f1[j]) / (X[j + i] - X[j]);
        }
        W[i] = f1[0];
    }
    return W;
}
long double SolveInT(long double t, vector<long double>& W, vector<long double>& X){
    int degree = W.size() - 1;
    long double result = W[degree];
    for (int i = degree - 1; i >= 0; i--) {
        result = result * (t - X[i]) + W[i];
    }
    return result;
}
int main(){
    int M, N;
    cin >> M;
    cin >> N;
    double x;
    vector<long double> X(M);
    vector<long double> Y(M);
    vector<long double> T(N);
    for (int i = 0; i < M; i++){
        cin >> x;
        X[i] = x;
    }
    for (int i = 0; i < M; i++){
        cin >> x;
        Y[i] = x;
    }
    for (int i = 0; i <N; i++){
        cin >> x;
        T[i] = x;
    }
    vector<long double> W = WSPinterpolacja(X, Y);
    for (int i = 0; i < W.size(); i++) cout << setprecision(17) << W[i] << " ";
    cout << endl;
    for (int i = 0; i < T.size(); i++) cout << setprecision(17) << SolveInT(T[i], W, X) << " ";
    cout << endl;
    return 0;
}