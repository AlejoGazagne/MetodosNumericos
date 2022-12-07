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
    double x[MAX], y1[MAX], y2[MAX], y3[MAX], k1[3], k2[3], k3[3], k4[3];
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

    file = fopen("resultadosRK4SistEDOs.txt", "w");

    if (file == nullptr) {
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    fprintf(file, "\tx\t\t\ty1\t\t\ty2\t\t\ty3\n");

    fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[0], y1[0], y2[0], y3[0]);

    for (int i = 1; i < n + 1; ++i) {
        x[i] = x[0] + i * h;

        k1[0] = f1(x[i - 1], y1[i - 1], y2[i - 1], y3[i - 1]);
        k1[1] = f2(x[i - 1], y1[i - 1], y2[i - 1], y3[i - 1]);
        k1[2] = f3(x[i - 1], y1[i - 1], y2[i - 1], y3[i - 1]);

        k2[0] = f1(x[i - 1] + h / 2., y1[i - 1] + k1[0] * h / 2., y2[i - 1] + k1[1] * h / 2.,
                   y3[i - 1] + k1[2] * h / 2.);
        k2[1] = f2(x[i - 1] + h / 2., y1[i - 1] + k1[0] * h / 2., y2[i - 1] + k1[1] * h / 2.,
                   y3[i - 1] + k1[2] * h / 2.);
        k2[2] = f3(x[i - 1] + h / 2., y1[i - 1] + k1[0] * h / 2., y2[i - 1] + k1[1] * h / 2.,
                   y3[i - 1] + k1[2] * h / 2.);

        k3[0] = f1(x[i - 1] + h / 2., y1[i - 1] + k2[0] * h / 2., y2[i - 1] + k2[1] * h / 2.,
                   y3[i - 1] + k2[2] * h / 2.);
        k3[1] = f2(x[i - 1] + h / 2., y1[i - 1] + k2[0] * h / 2., y2[i - 1] + k2[1] * h / 2.,
                   y3[i - 1] + k2[2] * h / 2.);
        k3[2] = f3(x[i - 1] + h / 2., y1[i - 1] + k2[0] * h / 2., y2[i - 1] + k2[1] * h / 2.,
                   y3[i - 1] + k2[2] * h / 2.);

        k4[0] = f1(x[i - 1] + h / 2., y1[i - 1] + k3[0] * h, y2[i - 1] + k3[1] * h, y3[i - 1] + k3[2] * h);
        k4[1] = f2(x[i - 1] + h / 2., y1[i - 1] + k3[0] * h, y2[i - 1] + k3[1] * h, y3[i - 1] + k3[2] * h);
        k4[2] = f3(x[i - 1] + h / 2., y1[i - 1] + k3[0] * h, y2[i - 1] + k3[1] * h, y3[i - 1] + k3[2] * h);

        y1[i] = y1[i - 1] + h * (k1[0] + 2. * k2[0] + 2. * k3[0] + k4[0]) / 6.;
        y2[i] = y2[i - 1] + h * (k1[1] + 2. * k2[1] + 2. * k3[1] + k4[1]) / 6.;
        y3[i] = y3[i - 1] + h * (k1[2] + 2. * k2[2] + 2. * k3[2] + k4[2]) / 6.;

        fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[i], y1[i], y2[i], y3[i]);
    }
}