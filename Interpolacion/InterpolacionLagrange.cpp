#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 2
#define FILAS 10

using namespace std;

void triangulacion(double m[10][10], int filas, int columnas);
void retrosustitucion(double m[10][10], int filas, int columnas, double x[]);
void pivoteo(double m[10][10], int filas, int columnas, int i);

//double funcion(double x) { return exp(-pow(x,2)); }
double funcion(double x) { return x+(2/x); }

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
    double node[filas][COLUMNAS];

    //Cargo los datos leidos en el array
    int j;
    for(int i = 0; i < filas; i++) {
        j = 0;
        do {
            fscanf(fp, "%lf", &(node[i][j]));
            j++;
        } while((c = fgetc(fp)) != '\n');
    }

    printf("numero de columnas= 2\n");

    //imprimo la matriz para verificar que lo leyo correctamente
    printf("-----------Nodos-----------\n");
    for(int i = 0; i < filas; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            printf("%lf ",node[i][j]);
        }
        printf("\n");
    }

    double x;
    printf("--------------------------\n");
    printf("Ingrese el valor a interpolar: ");
    scanf("%lf", &x);

    // CALCULAR P(x)
    double suma = 0;
    double error = 0;
    for(int k = 0; k < filas; k++){
        double producto = 1;
        for(int i = 0; i < filas; i++){
            if(i != k){
                producto = producto * (x - node[k][0])/(node[i][0]-node[k][0]);
            }
        }
        suma = suma + node[k][1]*producto;
        producto = 0;
    }

    error = fabs(funcion(x) - suma);
    printf("---------Resultados--------\n");
    printf("El valor de la suma es: %lf\n", suma);
    printf("El valor del error es: %lf\n", error);
    printf("---------------------------\n");

    // CALCULAR EL POLINOMIO INTERPOLADOR
    double A[10][10];
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < filas; j++){
            A[i][j] = pow(node[i][0], j);
        }
        A[i][filas] = node[i][1];
    }

    //imprimo la matriz para verificar que lo leyo correctamente
    for(int i = 0; i < filas; i++) {
        for(j = 0; j < filas; j++) {
            printf("%lf ",A[i][j]);
        }
        printf("\n");
    }

    triangulacion(A,filas, filas+1);
    double sol[filas];
    retrosustitucion(A, filas, filas+1, sol);

}
void triangulacion(double m[10][10], int filas, int columnas){
    // Triangulaciòn

    for (int i = 0; i < filas; i++) {
        pivoteo(m, filas, columnas, i);
        for (int j = i+1; j < filas; j++) {
            double factor = -m[j][i]/m[i][i];
            for (int k = 0; k <= columnas; k++) {
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

void retrosustitucion(double m[10][10], int filas, int columnas, double x[]){

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

void pivoteo(double m[10][10], int filas, int columnas, int i){
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