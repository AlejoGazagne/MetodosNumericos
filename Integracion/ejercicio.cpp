#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 2
#define FILAS 30

using namespace std;

double f(double x, double v) { return 10 * exp(0.05 * v * pow(x,0.02)); }

int main(){
    FILE *readPtr;
    readPtr = fopen("matrixBuild.txt", "w");

    double a, b, v = 0;
    int p;
    double c0, c1, c2, c3, c4, c5, x0, x1, x2, x3, x4, x5, i = 0;
    double m[FILAS][COLUMNAS];

    printf("Ingrese el valor de a: ");
    scanf("%lf", &a);
    printf("Ingrese el valor de b: ");
    scanf("%lf", &b);

    printf("Ingrese la cantidad de puntos: ");
    scanf("%d", &p);


    c0 = 0.5555556;
    c1 = 0.8888889;
    c2 = 0.5555556;
    x0 = -0.774596669;
    x1 = 0.;
    x2 = 0.774596669;

    while(v <= 50){
        i = ((b-a)/2)*(f(((b-a)*x0+(b+a))/2, v)*c0 + f(((b-a)*x1+(b+a))/2, v)*c1 + f(((b-a)*x2+(b+a))/2, v)*c2);
        fprintf(readPtr, "%lf\t%lf\n", v, i);
        v = v + 2.5;
    }

}
