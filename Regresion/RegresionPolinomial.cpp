#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 15
#define FILAS 10

using namespace std;

void triangulacion(double m[FILAS][COLUMNAS], int filas, int columnas);
void retrosustitucion(double m[FILAS][COLUMNAS], int filas, int columnas, double x[]);
void pivoteo(double m[FILAS][COLUMNAS], int filas, int columnas, int i);

int main() {
    FILE *fp;
    char ch;
    fp = fopen("nodos.dat","r");
    if ( fp == nullptr ) {
        puts ( "No se puede abrir el archivo");
    }

    //contador de filas
    int filas=0;
    char c;
    int maxValues = 0;

    while((c = fgetc(fp)) != EOF) {
        if(c == '\n'){
            filas++;
        }
    }

    printf("numero de filas=%i\n",filas);

    //cerramos y reabrimos el archivo para resetear el puntero
    fclose(fp);
    fp = fopen("nodos.dat","r");
    double n[filas][COLUMNAS];


    //Cargo los datos leidos en el array
    int j;
    for(int i = 0; i < filas; i++) {
        j = 0;
        do {
            fscanf(fp, "%lf", &(n[i][j]));
            j++;
        } while((c = fgetc(fp)) != '\n');
    }

    printf("numero de columnas= 2\n");

    //imprimo los nodos para verificar que lo leyo correctamente
    printf("Imprimo los nodos leidos\n");
    for(int i = 0; i < filas; i++) {
        for(j=0;j<COLUMNAS;j++) {
            printf("%lf ", n[i][j]);
        }
        int i1 = printf("\n");
    }

    // INGRESAR EL GRADO DEL POLINOMIO
    int p;
    printf("Ingrese el grado del polinomio: ");
    scanf("%d", &p);
    p = p+1;

    // ARMAR LA MATRIZ AUMENTADA
    double A[FILAS][COLUMNAS];
    for(int l = 0; l < p; l++){
        double sumaxy = 0;
        for(int i = 0; i < filas; i++){
            sumaxy = sumaxy + pow(n[i][0], l) * n[i][1];
        }
        A[l][p] = sumaxy;
        for(int m = 0; m < p; m++){
            double sumax = 0;
            for(int i = 0; i < filas; i++){
                sumax = sumax + pow(n[i][0], l + m);
            }
            A[l][m] = sumax;
        }
    }

    //imprimo la matriz para verificar que lo leyo correctamente
    printf("Verifico que se leyo bien la matriz\n");
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < p+1; j++) {
            printf("%lf ", A[i][j]);
        }
        int i1 = printf("\n");
    }

    triangulacion(A, p, p+1);
    double x[p];
    retrosustitucion(A, p, p+1, x);

    //CALCULAR EL ERROR
    double Ym = 0;
    double e = 0;
    double st = 0;
    double ecm = 0;
    double r = 0;

    for(int i = 0; i < filas; i++){
        double sum = 0;
        for(int j = 0; j < p; j++){
            sum = sum + x[j] * pow(n[i][0], j);
        }
        e = e + pow(n[i][1] - sum, 2);
        Ym = Ym + n[i][1];
    }
    Ym = Ym/(filas+1);
    for(int i = 0; i < filas; i++){
        st = st + pow(n[i][1] - Ym, 2);
    }
    r = sqrt(fabs(e-st)/st);
    ecm = sqrt(e/filas);

    printf("El error es de: %lf\n", e);
    printf("El error cuadratico medio es: %lf\n", ecm);
    printf("El coeficiente de correlacion es: %lf\n", r);
    printf("El st es: %lf", st);
}

void triangulacion(double m[FILAS][COLUMNAS], int filas, int columnas){
    // Triangulaciòn

    for (int i = 0; i < filas; i++) {
        pivoteo(m, filas, columnas, i);
        for (int j = i+1; j < filas; j++) {
            double factor = -m[j][i]/m[i][i];
            for (int k = 0; k < columnas; k++) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            m[j][columnas] = m[i][columnas] * factor + m[j][columnas];
        }
    }

    printf("\n");
    printf("Matriz reducida\n");

    for(int i = 0;i < filas; i++){
        for(int j = 0; j < columnas; j++){
            printf("%lf ", m[i][j]);
        }
        printf("\n");
    }

    // chequeo que determinante de la matriz no de = 0
    double det = 1.;
    for(int i = 0; i < filas; i++){
        det = det*m[i][i];
    }
    printf("\n");
    printf("El determinante de la matriz es: %lf\n", det);
    printf("\n");
}

void retrosustitucion(double m[FILAS][COLUMNAS], int filas, int columnas, double x[]){

    double value = 0.;
    value = m[filas-1][columnas-1]/m[filas-1][columnas-2];
    x[filas-1] = value;
    for(int i = filas-2; i >= 0; i--){
        double suma = 0.;
        for(int j = i+1 ; j < columnas-1; j++){
            suma = suma + m[i][j]*x[j];
        }
        value = (m[i][columnas-1]-suma)/m[i][i];
        x[i] = value;
    }

    for(int i = 0; i < filas; i++){
        printf("x%d: %lf\t", i + 1, x[i]);
    }
    printf("\n");
}

void pivoteo(double m[FILAS][COLUMNAS], int filas, int columnas, int i){
    int p = i;
    double tolerancia = pow(10, -3);

    if(fabs(m[i][i]) < tolerancia){
        for(int j = i+1; j < filas; j++){
            if(fabs(m[j][i]) > fabs(m[i][i])){
                for(int k = i; k < columnas-1; k++){
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
                double swap = m[i][columnas-1];
                m[i][columnas-1] = m[j][columnas-1];
                m[j][columnas-1] = swap;
            }
        }
    }
}