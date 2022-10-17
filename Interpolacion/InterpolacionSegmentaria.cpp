#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 2
#define FILAS 20

using namespace std;

void triangulacion(double m[FILAS][FILAS+1], int filas, int columnas);
void retrosustitucion(double m[FILAS][FILAS+1], int filas, int columnas, double x[]);
void pivoteo(double m[FILAS][FILAS+1], int filas, int columnas, int i);

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
    printf("-----------Nodos-----------\n");
    for(int i = 0; i < filas; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            printf("%lf ",n[i][j]);
        }
        printf("\n");
    }

    double A[FILAS][FILAS+1] = {0};
    int in = filas-1;

    for(int k = 0; k < in; k++){
        for(int j = 0; j <= 3; j++){
            A[2*k][4*k + j] = pow(n[k][0], 3-j);
            A[2*k+1][4*k+j] = pow(n[k+1][0], 3-j);
        }
        A[2*k][4*in] = n[k][1];
        A[2*k+1][4*in] = n[k+1][1];
    }


    for(int i = 2*in; i <= 3*in-2; i++){
        for(int k = 0; k <= in-2; k++){
            for(int j = 0; j <= 2; j++){
                A[i][4*k+j] = (3-j)*(pow(n[k+1][0], 2-j));
                A[i][4*(k+1)+j] = -(3-j)*(pow(n[k+1][0], 2-j));
            }
        }
        A[i][4*in+1] = 0;
    }


    for(int i = 3*in-1; i <= 4*in-3; i++){
        for(int k = 0; k <= in-2; k++){
            A[i][4*k] = 6*n[k+1][0];
            A[i][4*k+1] = 2;
            A[i][4*k+4] = (-6)*n[k+1][0];
            A[i][4*k+5] = -2;
        }
    }

    A[4*in-2][0] = 6*n[0][0];
    A[4*in-2][1] = 2;
    A[4*in-2][4*in+1] = 0;

    A[4*in-1][4*in-4] = 6*n[filas-1][0];
    A[4*in-1][4*in-3] = 2;
    A[4*in-1][4*in+1] = 0;

    //imprimo la matriz para verificar que lo leyo correctamente
    printf("-----------MATRIZ AMPLIADA-----------\n");
    for(int i = 0; i < 4*in; i++) {
        for(j = 0; j < 4*in +1; j++) {
            printf("%lf ",A[i][j]);
        }
        printf("\n");
    }

    triangulacion(A, 4*in, (4*in)+1);
    double x[filas];
    retrosustitucion(A, 4*in, (4*in)+1, x);

    //INTERPOLACION
    double valor = 0, resultado = 0;
    printf("Ingrese el valor a interpolar: ");
    scanf("%lf", &valor);
    if(n[0][0] <= valor && n[filas-1][0] >= valor){
        for(int i = 0; i < filas; i++){
            if(n[i+1][0] >= valor){
                resultado = x[4*i]*pow(valor, 3) + x[4*i+1]*pow(valor, 2) + x[4*i+2]*valor + x[4*i+3];
                break;
            }
        }
        printf("El valor interpolado de %lf es: %lf\n", valor, resultado);
    } else {
        printf("El valor a intepolar no se encuentra en el rango de los nodos\n");
    }

}
void triangulacion(double m[FILAS][FILAS+1], int filas, int columnas){
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

void retrosustitucion(double m[FILAS][FILAS+1], int filas, int columnas, double x[]){

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

void pivoteo(double m[FILAS][FILAS+1], int filas, int columnas, int i){
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