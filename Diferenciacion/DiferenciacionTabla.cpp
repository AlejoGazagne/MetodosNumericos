#include <cmath>
#include <iostream>
#include <cstdio>
#define FILAS 15
#define COLUMNAS 2

int main(){
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

    FILE *file;

    file = fopen("derivadas.txt", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    double h = (double) (node[filas - 1][0] - node[0][0]) / (filas - 1);
    double derivada;

    // Hacia adelante
    for(int i = 0; i < 2; i++){
        derivada = (-node[i + 2][1] + 4*node[i + 1][1] -3*node[i][1])/(2*h);
        fprintf(file, "%lf\t%lf\n", node[i][0], derivada);
    }
    // Centrado
    for(int i = 2; i < filas - 2; i++){
        derivada = (-node[i + 2][1] + 8*node[i + 1][1] - 8*node[i - 1][1] + node[i - 2][1])/(12*h);
        fprintf(file, "%lf\t%lf\n", node[i][0], derivada);
    }
    // Hacia atras
    for(int i = filas - 2; i < filas ; i++){
        derivada = (3*node[i][1] - 4*node[i - 1][1] + node[i - 2][1])/(2*h);
        fprintf(file, "%lf\t%lf\n", node[i][0], derivada);
    }

    return 0;
}