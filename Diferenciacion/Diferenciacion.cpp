#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define MAX 20

double f(double x){ return log(x)+1/x; }

int main(){
    FILE *file;

    file = fopen("derivadas.txt", "w");

    if(file == NULL){
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    double x0, xf, xi, n, h, fp;
    int op;

    printf("Ingrese el x0: ");
    scanf("%lf", &x0);
    printf("Ingrese el xf: ");
    scanf("%lf", &xf);
    printf("Ingrese la cantidad de intervalos: ");
    scanf("%lf", &n);
    h = (xf - x0)/n;
    printf("Seleccione el grado de la derivada\n1. Primer Grado\n2. Segundo Grado\n3. Tercer grado\n4. Cuarto Grado\n");
    scanf("%d", &op);

    switch(op){
        case 1:
            // Hacia adelante
            for(int i = 0; i < 2; i++){
                xi = x0 + i*h;
                fp = (-1*f(xi+2*h) + 4*f(xi+h) - 3*f(xi))/(2*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Centrado
            for(int i = 2; i < n-2; i++){
                xi = x0 + i*h;
                fp = (-1*f(xi+2*h) + 8*f(xi+h) - 8*f(xi-h) + f(xi-2*h))/(12*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Hacia atras
            for(int i = n-2; i < n+1; i++){
                xi = x0 + i*h;
                fp = (3*f(xi) - 4*f(xi-h) + f(xi-2*h))/(2*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }

            break;
        case 2:
            // Hacia adelante
            for(int i = 0; i < 3; i++){
                xi = x0 + i*h;
                fp = (-f(xi+3*h) + 4*f(xi+2*h) - 5*f(xi+h) + 2*f(xi))/(h*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Centrado
            for(int i = 3; i < n-3; i++){
                xi = x0 + i*h;
                fp = (-f(xi+2*h) + 16*f(xi+h) - 30*f(xi) + 16*f(xi-h) - f(xi-2*h))/(12*h*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Hacia atras
            for(int i = n-3; i < n+1; i++){
                xi = x0 + i*h;
                fp = (2*f(xi) - 5*f(xi-h) + 4*f(xi-2*h) - f(xi-3*h))/(h*h);
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            break;
        case 3:
            // Hacia adelante
            for(int i = 0; i < 4; i++){
                xi = x0 + i*h;
                fp = (-3*f(xi+4*h) + 14*f(xi+3*h) - 24*f(xi+2*h) + 18*f(xi+h)- 5*f(xi))/(2*pow(h,3));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Centrado
            for(int i = 4; i < n-4; i++){
                xi = x0 + i*h;
                fp = (-f(xi+3*h) + 8*f(xi+2*h) - 13*f(xi+1*h) + 13*f(xi-1*h) - 8*f(xi-2*h) + f(xi-3*h))/(8*pow(h,3));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Hacia atras
            for(int i = n-4; i < n+1; i++){
                xi = x0 + i*h;
                fp = (5*f(xi) - 18*f(xi-h) + 24*f(xi-2*h) - 14*f(xi-3*h) + 3*f(xi-4*h))/(2*pow(h,3));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            break;
        case 4:
            // Hacia adelante
            for(int i = 0; i < 4; i++){
                xi = x0 + i*h;
                fp = (-2*f(xi+5*h)+11*f(xi+4*h)-24*f(xi+3*h)+26*f(xi+2*h)-14*f(xi+h)+3*f(xi))/(pow(h,4));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Centrado
            for(int i = 4; i < n-4; i++){
                xi = x0 + i*h;
                fp = (-f(xi+3*h)+12*f(xi+2*h)-39*f(xi+h)+56*f(xi)-39*f(xi-h)+12*f(xi-2*h)-f(xi-3*h))/(6*pow(h,4));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            // Hacia atras
            for(int i = n-4; i < n+1; i++){
                xi = x0 + i*h;
                fp = (3*f(xi)-14*f(xi-h)+26*f(xi-2*h)-24*f(xi-3*h)+11*f(xi-4*h)-2*f(xi-5*h))/(pow(h,4));
                fprintf(file, "%lf\t%lf\n",xi , fp);
            }
            break;
        default:
            printf("La opcion ingresada es incorrecta\n");
            break;
    }


    for(int i = 0; i < n - 1; i++){

    }
}