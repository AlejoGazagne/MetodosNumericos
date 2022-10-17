#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 10
#define FILAS 10

using namespace std;

void triangulacion(double m[FILAS][COLUMNAS], int filas, int columnas);
void retrosustitucion(double m[FILAS][COLUMNAS], int filas, int columnas, double x[]);
void pivoteo(double m[FILAS][COLUMNAS], int filas, int columnas, int i);
double normaEuclidiana(double m[FILAS][COLUMNAS], int filas, int columnas);

int main() {
    FILE *fp;
    char ch;
    fp = fopen("datos.dat","r");
    if ( fp == nullptr ) {
        puts ( "No se puede abrir el archivo");
    }

    //contador de filas
    int filas=0;
    char c;
    int maxValues = 0;
    int columnas;

    while((c = fgetc(fp)) != EOF) {
        if(c == '\n'){
            filas++;
        }
    }

    printf("numero de filas=%i\n",filas);

    //cerramos y reabrimos el archivo para resetear el puntero
    fclose(fp);
    fp = fopen("datos.dat","r");
    double m[filas][10];


    //Cargo los datos leidos en el array
    int i, j;
    for(i = 0; i < filas; i++) {
        j = 0;
        do {
            fscanf(fp, "%lf", &(m[i][j]));
            j++;
        } while((c = fgetc(fp)) != '\n');
    }

    columnas = j;

    printf("numero de columnas= %i\n",columnas);

    //imprimo la matriz para verificar que lo leyo correctamente
    printf("matriz leida\n");
    for(i=0;i<filas;i++) {
        for(j=0;j<columnas;j++) {
            printf("%lf ",m[i][j]);
        }
        printf("\n");
    }

    double x[filas];
    double norma = normaEuclidiana(m, filas, columnas);

    triangulacion(m, filas, columnas);
    retrosustitucion(m, filas, columnas, x);

    printf("\n");
    printf("La norma euclidiana es: %lf\n", norma);

}
double normaEuclidiana(double m[FILAS][COLUMNAS], int filas, int columnas){
    // NORMA EUCLIDIANA
    double norma = 1;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < filas; j++){
            norma = norma + pow(m[i][j],2);
        }
    }
    norma = sqrt(norma);

}

void triangulacion(double m[FILAS][COLUMNAS], int filas, int columnas){
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

void retrosustitucion(double m[FILAS][COLUMNAS], int filas, int columnas, double x[]){

    x[filas-1] = m[filas-1][columnas-1]/m[filas-1][columnas-2];

    for(int i = filas-1; i >= 0; i--){
        double suma = 0.;
        for(int j = i+1 ; j < columnas; j++){
            suma = suma + m[i][j]*x[j];
        }
        x[i] = (m[i][columnas-1]-suma)/m[i][i];
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