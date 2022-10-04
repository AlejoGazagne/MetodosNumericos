#include <cmath>
#include <iostream>
#define FILAS 10
#define COLUMNAS 10

int main(){
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

    //imprimo la matriz para verificar que se leyo correctamente
    for(i=0;i<filas;i++) {
        for(j=0;j<columnas;j++) {
            printf("%lf ",m[i][j]);
        }
        printf("\n");
    }

    // VERIFICAR SI ES DIAGONALMENTE DOMiNANTE
    for(int i = 0; i < filas; i++){
        double suma = 0.;
        for(int j = 0; j < columnas-1; j++){
            if(i != j){
                suma = suma + fabs(m[i][j]);
            }
        }
        if(fabs(m[i][i]) <= suma){
            printf("La matriz no es digonalmente dominante\n");
        }
    }

    double xv[FILAS] = {0.};
    double xn[FILAS] = {0.};
    double tolerancia = pow(10,-4);
    double error = 0.;
    int iter = 0;
    do{
        error = 0.;
        iter++;

        for (int i = 0; i < filas; i++) {
            double sum = 0;
            for (int j = 0; j < columnas; j++) {
                if (i != j) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (m[i][columnas-1] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }

        error = sqrt(error);
    } while(tolerancia < error && iter < 10000);

    if(iter == 10000) printf("Limite de iteraciones alcanzado\n");

    printf("El conjunto solucion es: \n");
    for(int i = 0;i < filas; i++){
        printf("x%d: %lf ", i+1, xn[i]);
    }
    printf("\n");
    printf("Error: %.12lf, en %d iteraciones\n", error, iter);
}
/*
void banda(double m[MAXROW][MAXCOL], double b[MAXROW], int *rows, int *columns) {
    *rows = MAXROW;
    *columns = MAXCOL;
    for (int i = 0; i < MAXROW; i++) {
        for (int j = 0; j < MAXCOL; j++) {
            if (i == 0 && j == 0) {
                m[i][j] = 1;
            } else if (i == MAXROW-1 && j == MAXROW-1) {
                m[i][j] = 1;
            } else if (j == i - 1 && i != MAXROW -1) {
                m[i][j] = 1;
            } else if (j == i) {
                m[i][j] = -2;
            } else if (j == i + 1 && i != 0) {
                m[i][j] = 1;
            } else {
                m[i][j] = 0;
            }
            b[i] = 1;
        }
    }
}
*/