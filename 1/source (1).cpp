//Maryia Babinskaya
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
// b^2 = a * c wlasnosc ciagu geometrycznego
// b/q + b + b*q = S
// a + b + c = S
// a * b * c = P

void print(float a, float b, float c, int &N){
    cout << setprecision(10) << scientific << a << " " << b << " " << c << endl;
    N = N - 1;
}

int main(){
    int N;
    float ai, bi, ci;
    cin >> N;
    while(N > 0) {
        float Pi;
        float Si;
        cin >> Pi >> Si;
        if (Pi == 0 || Si == 0){
            print(0,0,0,N);
            continue;
        }
        bi = cbrtf(Pi);
        float diskriminant = (1 - Si / bi) * (1 - Si / bi) - 4;
        if (diskriminant < 0){
            print(0,0,0,N);
            continue;
        }
        if (diskriminant == 0){
           float r1 = (- 1 + Si / bi ) / 2;
           ai = bi / r1;
           ci = bi * r1;
           if(ai >= ci) print(ai,bi,ci,N);
           else print(ci,bi,ai,N);
           continue;
        }
        else { // diskriminant > 0
            float r1 = (- 1 + Si / bi + sqrt(diskriminant)) / 2;
            if(r1 == 0){
                float r2 = (- 1 + Si / bi - sqrt(diskriminant)) / 2;
                ai = bi / r2;
                ci = bi * r2;
                if(ai >= ci) print(ai,bi,ci,N);
                else print(ci,bi,ai,N);
                continue;
            }
            ai = bi / r1;
            ci = bi * r1;
            if(ai >= ci) print(ai,bi,ci,N);
            else print(ci,bi,ai,N);
            continue;
        }
    }
    return 0;
}