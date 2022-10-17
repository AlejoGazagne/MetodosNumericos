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

    if(n%2 != 0){
        printf("El numero de subintervalos debe ser par\n");
        return 0;
    }
    h = (b-a)/n;
    double suma = f(a) + f(b);
    for(int i = 1; i < (n/2); i++){
        double x = a + 2*i*h;
        suma = suma + 2*f(x)+ 4*f(x-h);
    }
    suma = (h/3) *(suma + 4*f(b-h));

    printf("El valor de la integral es: %lf\n", suma);

}