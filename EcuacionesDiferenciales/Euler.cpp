#include <cstdio>
#include <iostream>
#include <cmath>
#define MAX 10000

using namespace std;

//double f(double x, double y){ return (1+x)*sqrt(y); }
//double f(double x, double y){ return x*x - y; }
double f(double x, double y){ return exp(-2*x) - 2*y; }
//double f(double x, double y) {return (4*y-x*x)*y;}
//dv = 10 - 0.01*pow(v, 3/2) -> = 10 - 0.01*pow(y, 3/2)
//dt
//double F(double x) {return pow(x/2+pow(x,2)/4+1,2);}

int main(){
    FILE *file;

    file = fopen("Euler.txt", "w");

    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    int n;
    double xf, xp, yp, h, x[MAX], y[MAX], y2[MAX], y3[MAX];

    printf("Ingrese el valor de x0: ");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor de xf: ");
    scanf("%lf", &xf);
    printf("Ingrese el valor de y0: ");
    scanf("%lf", &y[0]);
    printf("Ingrese la cantidad de intervalos: ");
    scanf("%d", &n);
    y2[0] = y[0];
    y3[0] = y[0];
    h = (xf-x[0])/n;

    // Calculamos y1
    for(int i = 0; i < n + 1; i++){
        y[i+1] = y[i] + h*f(x[i], y[i]);
        x[i+1] = x[i] + h;
        fprintf(file, "%lf\t%.12lf\n",x[i] , y[i]);
        //fprintf(file, "%lf\t%.12lf\terror: %lf\n",x[i] , y[i], fabs(y[i]-F(x[i])));//error exacto
    }

    // Calculamos y2
    for(int i = 0; i < n;i++){
        yp = y2[i] + (h/2)*f(x[i], y2[i]);
        xp = x[i] + h/2;
        y2[i+1] = yp + (h/2)*f(xp, yp);
    }

    // Calculamos y3
    for(int i = 0; i < n; i++){
        yp = y3[i] + (h/4)*f(x[i], y[i]);
        xp = x[i] + h/4;
        yp = yp + (h/4)*f(xp, yp);
        xp = xp + h/4;
        yp = yp + (h/4)*f(xp, yp);
        xp = xp + h/4;
        y3[i+1] = yp + (h/4)*f(xp, yp);
    }
    fclose(file);

    return 0;
}