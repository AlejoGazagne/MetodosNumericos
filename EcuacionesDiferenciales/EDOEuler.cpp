#include <cstdio>
#include <cmath>
#define MAX 150

double f1(double x, double y1, double y2, double y3) {
    return -y1*x + 4*sin(x);
}

double f2(double x, double y1, double y2, double y3) {
    return -y1+4*cos(x);
}

double f3(double x, double y1, double y2, double y3) {
    return 0;
}

int main(){
    double x[MAX], y1[MAX], y2[MAX], y3[MAX];
    double h;
    int n;

    printf("Ingrese el valor inicial (x0) \n");
    scanf("%lf", &x[0]);
    printf("Ingrese el valor final (xf) \n");
    scanf("%lf", &x[MAX - 1]);
    printf("Ingrese el dato inicial (y10) \n");
    scanf("%lf", &y1[0]);
    printf("Ingrese el dato inicial (y20) \n");
    scanf("%lf", &y2[0]);
    printf("Ingrese el dato inicial (y30) \n");
    scanf("%lf", &y3[0]);
    printf("Ingrese la cantidad de subintervalos (n) \n");
    scanf("%d", &n);

    h = (x[MAX - 1] - x[0]) / n;

    FILE *file;

    file = fopen("resultadosEulerSistEDOs.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    fprintf(file, "\tx\t\t\ty1\t\t\ty2\t\t\ty3\n");

    for (int i = 0; i < n + 1; ++i) {

        x[i + 1] = x[i] + h;
        y1[i + 1] = y1[i] + h * f1(x[i], y1[i], y2[i], y3[i]);
        y2[i + 1] = y2[i] + h * f2(x[i], y1[i], y2[i], y3[i]);
        y3[i + 1] = y3[i] + h * f3(x[i], y1[i], y2[i], y3[i]);
        fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[i], y1[i], y2[i], y3[i]);
    }
}