//Maryia Babinskaya
#include <iostream>
#include <cmath>
#include <iomanip>
#include "funkcja.h"
using namespace std;
//template <typename T>
//T funkcja(const T & x, const T & y){
//    T w = sin(x*x - 2*(y+1))/exp(-y*y+cos(x*y));
//    return w;
//}
struct DZET {
    double value;
    double derivativeX, derivativeY;
    double derivativeXX, derivativeYY, derivativeXY;
    //domyslny konstruktor
    DZET() {
        value = 0.0;
        derivativeX = 0.0;
        derivativeY = 0.0;
        derivativeXX = 0.0;
        derivativeYY = 0.0;
        derivativeXY = 0.0;
    }
    //konstruktor tylko dla wartosci funkcji
    DZET(double x) {
        value = x;
        derivativeX = 0.0;
        derivativeY = 0.0;
        derivativeXX = 0.0;
        derivativeYY = 0.0;
        derivativeXY = 0.0;
    }
    //konstruktor dla funkcji i pochodnych
    DZET(double x, double dx, double dy, double dxx, double dyy, double dxy) {
        value = x;
        derivativeX = dx;
        derivativeY = dy;
        derivativeXX = dxx;
        derivativeYY = dyy;
        derivativeXY = dxy;
    }
    DZET(double value, double other) : DZET(value) {
        if(other == 1){
            derivativeX = true;
            derivativeY = false;
        }
        else if(other == 2){
            derivativeX = false;
            derivativeY = true;
        }
        else{
            derivativeX = false;
            derivativeY = false;
        }
    }
    DZET operator+(DZET& other) const { ////////////////////////////////////////////////////////////////////////////////
        return DZET(value + other.value, derivativeX + other.derivativeX, derivativeY + other.derivativeY, derivativeXX + other.derivativeXX, derivativeYY + other.derivativeYY, derivativeXY + other.derivativeXY);
    }
    friend DZET operator+(const DZET& f, const DZET& g){
        return DZET(f.value + g.value, f.derivativeX + g.derivativeX, f.derivativeY + g.derivativeY, f.derivativeXX + g.derivativeXX, f.derivativeYY + g.derivativeYY, f.derivativeXY + g.derivativeXY);
    }
    friend DZET operator-(const DZET& other){
        return DZET(-other.value, -other.derivativeX, -other.derivativeY, -other.derivativeXX, -other.derivativeYY, -other.derivativeXY);
    }
    friend DZET operator-(DZET& f, DZET& g){ ///////////////////////////////////////////////////////////////////////////
        return DZET(f.value - g.value, f.derivativeX - g.derivativeX, f.derivativeY - g.derivativeY, f.derivativeXX - g.derivativeXX, f.derivativeYY - g.derivativeYY, f.derivativeXY - g.derivativeXY);
    }
    DZET operator*(DZET& other) const { ////////////////////////////////////////////////////////////////////////////////
        return DZET(value * other.value, derivativeX * other.value + value * other.derivativeX, derivativeY * other.value + value * other.derivativeY, derivativeXX * other.value + value * other.derivativeXX, derivativeYY * other.value + value * other.derivativeYY, derivativeXY * other.value + value * other.derivativeXY);
    }
    friend DZET operator*(const DZET& f, const DZET& g){
        return DZET(f.value * g.value, f.derivativeX * g.value + g.derivativeX * f.value, f.derivativeY * g.value + g.derivativeY * f.value, 2 * f.derivativeX * g.derivativeX + f.derivativeXX * g.value + g.derivativeXX * f.value, 2 * f.derivativeY * g.derivativeY + f.derivativeYY * g.value + g.derivativeYY * f.value, f.derivativeXY * g.value + g.derivativeY * f.derivativeX + g.derivativeXY * f.value + f.derivativeY * g.derivativeX);
    }
    DZET operator/(DZET& other) const { ////////////////////////////////////////////////////////////////////////////////
        return DZET(value / other.value, (derivativeX * other.value - value * other.derivativeX) / (other.value * other.value), (derivativeY * other.value - value * other.derivativeY) / (other.value * other.value), (derivativeXX * other.value - value * other.derivativeXX) / (other.value * other.value), (derivativeYY * other.value - value * other.derivativeYY) / (other.value * other.value), (derivativeXY * other.value - value * other.derivativeXY) / (other.value * other.value));
    }
    friend DZET operator/(const DZET& f, const DZET& g){
        return DZET(f.value / g.value, (f.derivativeX * g.value - f.value * g.derivativeX) / pow(g.value, 2), (f.derivativeY * g.value - f.value * g.derivativeY) / pow(g.value, 2), (-g.value * (2 * f.derivativeX * g.derivativeX + f.value * g.derivativeXX) + f.derivativeXX * pow(g.value, 2) + 2 * f.value * pow(g.derivativeX,2)) / pow(g.value, 3), (-g.value * (2 * f.derivativeY * g.derivativeY + f.value * g.derivativeYY) + f.derivativeYY * pow(g.value, 2) + 2 * f.value * pow(g.derivativeY,2)) / pow(g.value, 3), (-g.value * (f.derivativeX * g.derivativeY + f.derivativeY * g.derivativeX + f.value * g.derivativeXY) + f.derivativeXY * pow(g.value,2) + 2 * f.value * g.derivativeX * g.derivativeY) / pow(g.value,3));
    }
    friend DZET operator-(const DZET& f, const DZET& g){
        return f + (-g);
    }
    friend ostream& operator <<(ostream& output, const DZET& other){
        return output << other.value << " " << other.derivativeX << " " << other.derivativeY  << " " << other.derivativeXX << " " << other.derivativeXY << " " << other.derivativeYY;
    }
    friend DZET sin(const DZET& f){
        return DZET(sin(f.value),cos(f.value) * f.derivativeX,cos(f.value) * f.derivativeY,cos(f.value) * f.derivativeXX - sin(f.value) * pow(f.derivativeX,2),cos(f.value) * f.derivativeYY - sin(f.value) * pow(f.derivativeY,2),cos(f.value) * f.derivativeXY - sin(f.value) * f.derivativeX * f.derivativeY);
    }
    friend DZET cos(const DZET& f){
        return DZET(cos(f.value),-sin(f.value) * f.derivativeX,-sin(f.value) * f.derivativeY,-cos(f.value) * pow(f.derivativeX,2) - sin(f.value) * f.derivativeXX,-cos(f.value) * pow(f.derivativeY,2) - sin(f.value) * f.derivativeYY,-cos(f.value) * f.derivativeX * f.derivativeY - sin(f.value) * f.derivativeXY);
    }
    friend DZET exp(const DZET& f){
        return DZET(exp(f.value),exp(f.value) * f.derivativeX,exp(f.value) * f.derivativeY,exp(f.value) * (pow(f.derivativeX,2) + f.derivativeXX),exp(f.value) * (pow(f.derivativeY,2) + f.derivativeYY),exp(f.value) * (f.derivativeX * f.derivativeY + f.derivativeXY));
    }
};
int main(){
    int N;
    cin >> N;
    for(int i = 0; i < N; i++){
        double x, y;
        cin >> x >> y;
        cout << setprecision(15) << funkcja(DZET(x, 1), DZET(y, 2)) <<  "\n";
    }
    return 0;
}
//4
//0.0 1.0
//1.0 -1.0
//-2.0 2.0
//10.0 0.1

//0.756802495307928  0.00000000000000   2.82089223234308 -0.550484746419296  0.00000000000000 6.74275395752475
//1.33254939776314   2.83254191138382  -5.49764070691010  0.924483034856005 -5.99962825432166 18.5387068096272
//-95.4459944863016  30.2587880515848  -149.953283536275  1999.58989772411   649.252143179076 284.818881946363
//-0.23489123252023 -10.8099926844176  -0.94449708714517  91.0586053228664  -102.754369536573 -11.062545637455