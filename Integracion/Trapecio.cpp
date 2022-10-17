#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>

double f(double x){ return -2*pow(x-2,2)+2; }

int main(){
    double a, b, h;
    int n;
    printf("Ingrese los limites de intefracion: \n");
    printf("Inferior: ");
    scanf("%lf", &a);
    printf("Superior: ");
    scanf("%lf", &b);
    printf("Ingrese el numero de sub-intervalos: ");
    scanf("%d", &n);

    double suma = f(a) + f(b);
    h = (b-a)/n;
    for(int i = 0; i < n; i++){
        suma = suma + 2*f(a+i*h);
    }
    suma = suma * h/2;

    printf("El valor de la integral es: %lf\n", suma);

}