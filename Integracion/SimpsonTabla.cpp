#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
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

    double a, b, h;
    int n;

    printf("Ingrese los limites de integracion: \n");
    printf("Inferior: ");
    scanf("%lf", &a);
    printf("Superior: ");
    scanf("%lf", &b);

    n = filas -1;
    h = (b-a)/n;

    if (n % 2 != 0) {
        printf("El numero de intervalos debe ser par\n");
        return 0;
    }

    double suma = node[0][1] + node[filas-1][1];
    for(int i = 1; i < n/2; i++){
        suma = suma + 2*node[2*i][1] + 4*node[2*i - 1][1];
    }

    suma = (h/3)*(suma + 4*node[filas - 2][1]);

    printf("El valor de la integral es de %lf", suma);
}