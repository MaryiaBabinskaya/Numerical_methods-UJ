//Maryia Babinskaya
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int N, M;
    cin >> N;
    cin >> M;
    vector<double> wstegi[M+1];
    double x;
    for(int i = 0; i < M + 1; i++){
        for(int  j = 0; j < N - M + i; j++) {
            cin>>x;
            wstegi[i].push_back(x);
        }
    }
    vector<double> prawaStorna(N);
    for (int i = 0; i < N; i++){
        cin >> x;
        prawaStorna[i] = x;
    }
    vector<double> wektorpoczatek(N);
    for (int i = 0; i < N; i++){
        cin >> x;
        wektorpoczatek[i] = x;
    }
    double w;
    cin >> w;
    int liczbaiteracji;
    cin >> liczbaiteracji;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(int it = 0; it < liczbaiteracji; it++){
        for(int i = 0; i < N; i++) {
            double sigma = prawaStorna[i];
            for(int m = 0; m < M; m++){
                if(i - M + m >= 0)
                    sigma -= wstegi[m][i - M + m] * wektorpoczatek[i - M + m];
            }
            for(int m = 0; m < M; m++){
                if(i + m + 1 < N)
                    sigma -= wstegi[M - 1 - m][i] * wektorpoczatek[i + m + 1];
            }
            wektorpoczatek[i] = (1 - w) * wektorpoczatek[i] + w * sigma/wstegi[M][i];
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < N; i++) {
        cout << setprecision(15) << wektorpoczatek[i] << endl;
    }
    return 0;
}
