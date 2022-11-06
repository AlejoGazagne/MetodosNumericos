#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>

double f(double x){ return pow((1-x),3); }

int main(){
    double a, b, h, x;
    int n;
    printf("Ingrese los limites de integracion: \n");
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
        x = a + 2*i*h;
        suma = suma + 2*f(x)+ 4*f(x-h);
    }
    suma = (h/3) *(suma + 4*f(b-h));

    printf("El valor de la integral es: %.20lf\n", suma);

}