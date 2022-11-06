#include <cstdio>
#include <iostream>
#include <cmath>
#define MAX 10000

using namespace std;

double f(double x, double y) {return -2*x*y;}
double fp(double x, double y){return -2*y;}

int main(){
    FILE *file;

    file = fopen("PuntoMedio.txt", "w");

    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    int n;
    double xf, h, ym, xm, x[MAX], y[MAX];

    printf("Ingrese el valor de x0: ");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor de xf: ");
    scanf("%lf", &xf);
    printf("Ingrese el valor de y0: ");
    scanf("%lf", &y[0]);
    printf("Ingrese la cantidad de intervalos: ");
    scanf("%d", &n);
    h = (xf-x[0])/n;

    for(int i = 0; i < n;i++){
        xm = x[i] + h/2;
        ym = y[i] + (h/2)*f(x[i], y[i]);
        y[i+1] = y[i] + h*f(xm, ym);
        x[i+1] = x[i] + h;
        fprintf(file, "%lf\t%lf\n",x[i+1] , y[i+1]);
    }
    fclose(file);
}