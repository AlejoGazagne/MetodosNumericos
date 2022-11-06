#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 2
#define FILAS 10

using namespace std;

double f(double x) { return sin(x+1)/(x+1); }

int main(){
    double a, b;
    int p;
    double c0, c1, c2, c3, c4, c5, x0, x1, x2, x3, x4, x5, i = 0;

    printf("Ingrese el valor de a: ");
    scanf("%lf", &a);
    printf("Ingrese el valor de b: ");
    scanf("%lf", &b);

    printf("Ingrese la cantidad de puntos: ");
    scanf("%d", &p);

    switch(p){
        case 2:
            c0 = 1.;
            c1 = 1.;
            x0 = -1/sqrt(3);
            x1 = 1/sqrt(3);
            i = ((b-a)/2)*(f(((b-a)*x0+(b+a))/2)*c0 + f(((b-a)*x1+(b+a))/2)*c1);
            break;
        case 3:
            c0 = 0.5555556;
            c1 = 0.8888889;
            c2 = 0.5555556;
            x0 = -0.774596669;
            x1 = 0.;
            x2 = 0.774596669;
            i = ((b-a)/2)*(f(((b-a)*x0+(b+a))/2)*c0 + f(((b-a)*x1+(b+a))/2)*c1 + f(((b-a)*x2+(b+a))/2)*c2);
            break;
        case 4:
            c0 = 0.3478548;
            c1 = 0.6521452;
            c2 = 0.6521452;
            c3 = 0.3478548;
            x0 = -0.861136312;
            x1 = -0.339981044;
            x2 = 0.339981044;
            x3 = 0.861136312;
            i = ((b-a)/2)*(f(((b-a)*x0+(b+a))/2)*c0 + f(((b-a)*x1+(b+a))/2)*c1 + f(((b-a)*x2+(b+a))/2)*c2 + f(((b-a)*x3+(b+a))/2)*c3);
            break;
        case 5:
            c0 = 0.2369269;
            c1 = 0.4786287;
            c2 = 0.5688889;
            c3 = 0.4786287;
            c4 = 0.2369269;
            x0 = -0.906179846;
            x1 = -0.538469310;
            x2 = 0.0;
            x3 = 0.538469310;
            x4 = 0.906179846;
            i =  ((b-a)/2)*(f(((b-a)*x0+(b+a))/2)*c0 + f(((b-a)*x1+(b+a))/2)*c1 + f(((b-a)*x2+(b+a))/2)*c2 + f(((b-a)*x3+(b+a))/2)*c3 + f(((b-a)*x4+(b+a))/2)*c4);
            break;
        case 6:
            c0 = 0.1713245;
            c1 = 0.3607616;
            c2 = 0.4679139;
            c3 = 0.4679139;
            c4 = 0.3607616;
            c5 = 0.1713245;
            x0 = -0.932469514;
            x1 = -0.661209386;
            x2 = -0.238619186;
            x3 = 0.238619186;
            x4 = 0.661209386;
            x5 = 0.932469514;
            i =  ((b-a)/2)*(f(((b-a)*x0+(b+a))/2)*c0 + f(((b-a)*x1+(b+a))/2)*c1 + f(((b-a)*x2+(b+a))/2)*c2 + f(((b-a)*x3+(b+a))/2)*c3 + f(((b-a)*x4+(b+a))/2)*c4 + f(((b-a)*x5+(b+a))/2)*c5);
            break;
        default:
            printf("So joda????\n");
            return 0;
            break;
    }

    printf("El valor de la integral es: %.12lf\n", i);
}