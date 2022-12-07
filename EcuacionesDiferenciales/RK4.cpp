#include <cstdio>
#include <iostream>
#include <cmath>
#define MAX 10000

using namespace std;

//double f(double x, double y) {return 1+x*sin(y*x);}
double f(double x, double y) {return (4*y-x*x)*y;}

int main(){
    FILE *file;

    file = fopen("RK4.txt", "w");

    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    int n;
    double xf, h, x[MAX], y[MAX], k[5];

    printf("Ingrese el valor de x0: ");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor de xf: ");
    scanf("%lf", &xf);
    printf("Ingrese el valor de y0: ");
    scanf("%lf", &y[0]);
    printf("Ingrese la cantidad de intervalos: ");
    scanf("%d", &n);
    h = (xf-x[0])/n;

    for (int i = 0; i < n; i++){
        k[1] = f(x[i],y[i]);
        k[2] = f(x[i] + h, y[i] + k[1]*h/2);
        k[3] = f(x[i] + h/2, y[i] + k[2]*h/2);
        k[4] = f(x[i] + h, y[i] + k[3]*h);
        y[i+1] = y[i] + h*(k[1]+2*k[2]+2*k[3]+k[4])/6;
        x[i+1] = x[i] + h;
        fprintf(file, "%lf\t%lf\n",x[i+1] , y[i+1]);
    }
    fclose(file);
}