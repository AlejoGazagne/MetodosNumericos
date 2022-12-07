#include <cmath>
#include <iostream>
#define FILAS 15
#define COLUMNAS 16

void escritura(double m[FILAS][COLUMNAS]);

int main(){
    /*FILE *fp;
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
    }*/

    //Para usar la banda, las columnas y las filas deben estar bien definidas
    int filas=0;
    char c;
    int maxValues = 0;
    int columnas;
    double m[FILAS][COLUMNAS] = {0.};
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(i == j){
                if(i==0){
                    m[i][j] = 1;
                    m[i][COLUMNAS-1] = 1;
                } else if(i == FILAS-1){
                    m[i][j] = 1;
                    m[i][COLUMNAS-1] = 1;
                } else {
                    m[i][j-1] = 1;
                    m[i][j] = -2;
                    m[i][j+1] = 1;
                    m[i][COLUMNAS-1] = 1;
                }
            }
        }
    }
    filas = FILAS;
    columnas = COLUMNAS;
    //imprimo la matriz para verificar que se leyo correctamente
    for(int i=0;i<filas;i++) {
        for(int j=0;j<columnas;j++) {
            printf("%d ",(int) m[i][j]);
        }
        printf("\n");
    }
    escritura(m);
    // FIN de BANDA

    // VERIFICAR SI ES DIAGONALMENTE DOMiNANTE
    for(int t = 0; t < filas; t++){
        double suma = 0.;
        for(int k = 0; k < columnas - 1; k++){
            if(t != k){
                suma = suma + fabs(m[t][k]);
            }
        }
        if(fabs(m[t][t]) <= suma){
            printf("La matriz no es digonalmente dominante\n");
        }
    }

    double xv[FILAS] = {0.};
    double xn[FILAS] = {0.};
    double tolerancia = pow(10,-8);
    double error = 0.;
    int iter = 0;
    do{
        error = 0.;
        iter++;
        for (int t = 0; t < filas; t++) {
            double sum = 0.;
            for (int k = 0; k < columnas - 1; k++) {
                if (t != k) {
                    sum = sum + m[t][k] * xv[k];
                }
            }
            xn[t] = (m[t][columnas-1] - sum) / m[t][t];
            error = error + pow((xn[t] - xv[t]), 2);
            xv[t] = xn[t];
        }
        error = sqrt(error);
    } while(tolerancia < error && iter < 1000);

    if(iter == 10000) printf("Limite de iteraciones alcanzado\n");

    printf("El conjunto solucion es: \n");
    for(int i = 0;i < filas; i++){
        printf("x%d: %lf\t", i+1, xn[i]);
    }
    printf("\n");
    printf("Error: %.12lf, en %d iteraciones\n", error, iter);
}

void escritura(double m[FILAS][COLUMNAS]) {

    FILE *readPtr;
    int j, i, n;
    double k;
    readPtr = fopen("matrixBuild.txt", "w");
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS-1; j++) {
            fprintf(readPtr, "%lf\t", m[i][j]);
        }
        fprintf(readPtr, "%lf\n", m[i][COLUMNAS-1]);
    }
    fclose(readPtr);
}