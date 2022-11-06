/*#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#define COLUMNAS 2
#define FILAS 12

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
        for(int t = 0; t <= 3; t++){
            A[2*k][4*k + t] = pow(n[k][0], 3-t);
            A[2*k+1][4*k+t] = pow(n[k+1][0], 3-t);
        }
        A[2*k][4*in] = n[k][1];
        A[2*k+1][4*in] = n[k+1][1];
    }

    for(int i = 2*in; i <= 3*in-2; i++){
        for(int k = 0; k < in-2; k++){
            for(int t = 0; t <= 2; t++){
                A[i][4*k+t] = (3-t)*(pow(n[k+1][0], 2-t));
                A[i][4*(k+1)+t] = -(3-t)*(pow(n[k+1][0], 2-t));
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
}*/

#include <cstdio>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>

using namespace std;

int main(void) {

    FILE *fp;
    char ch;
    fp = fopen("nodos.dat", "r");
    if (fp == NULL) {
        puts("No se puede abrir el archivo");
    }

    //contador de filas
    int filas = 0;
    char c;
    int maxValues = 0;
    int columnas;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            filas++;
        }
    }

    printf("numero de filas=%i\n", filas);

    rewind(fp);
    double x[filas];
    double y[filas]; //Termino independiente


    //Cargo los datos leidos en el array
    int xi = 0;
    int yi = 0;
    int j = 0;
    int i;
    for (i = 0; i < filas; i++) {
        j = 0;

        do {
            if (j == 0) {
                fscanf(fp, "%lf", &(x[xi]));
                xi++;
                j++;
            } else {
                fscanf(fp, "%lf", &(y[yi]));
                yi++;
            }
        } while ((c = fgetc(fp)) != '\n');

    }

    columnas = j;

    printf("numero de columnas=%i\n\n", columnas);

    //imprimo la matriz para verificar que lo leyo correctamente

    printf("LOS ELEMENTOS DE LA TABLA SON:\n");

    for (i = 0; i < filas; i++) {
        printf("%lf \t %lf", x[i], y[i]);
        printf("\n");
    }

    //Puntos deben estar ordenados!

    printf("SPLINE CUBICA NATURAL\n");

    int n = filas;

    //Error real: valor real - valor del metodo
    //Error relativo: (valor real - valor del metodo) / valor real
    //Error porcentual : idem del de arriba, pero multiplicarlo por 100.

    //tengo 4(n-1) incognitas
    int N = 4 * (n - 1) + 1; // N total
    double m[N][N];
    double b[N];
    double aux;
    double valor; //valor buscado
    double resultado; // solucion!!

    printf("Cantidad de puntos: \n", n);

    //inicializo mis matrices en cero
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            m[i][j] = 0;
        b[i] = 0;
    }

    //Polinomios
    for (int i = 1; i < n; i++) {
        m[i * 2 - 1][i * 4 - 3] = 1;
        m[i * 2 - 1][i * 4 - 2] = x[i - 1];
        m[i * 2 - 1][i * 4 - 1] = pow(x[i - 1], 2);
        m[i * 2 - 1][i * 4] = pow(x[i - 1], 3);
        b[i * 2 - 1] = y[i - 1];

        m[i * 2][i * 4 - 3] = 1;
        m[i * 2][i * 4 - 2] = x[i + 1 - 1];
        m[i * 2][i * 4 - 1] = pow(x[i + 1 - 1], 2);
        m[i * 2][i * 4] = pow(x[i + 1 - 1], 3);
        b[i * 2] = y[i + 1 - 1];
    }


    //Derivadas Primeras
    j = 2 * (n - 1);
    for (int i = 2; i <= n - 1; i++) {
        m[j + i - 1][(i - 1) * 4 - 3] = 0;
        m[j + i - 1][(i - 1) * 4 - 2] = 1;
        m[j + i - 1][(i - 1) * 4 - 1] = 2 * x[i - 1];
        m[j + i - 1][(i - 1) * 4] = 3 * pow(x[i - 1], 2);

        m[j + i - 1][(i - 1) * 4 + 1] = 0;
        m[j + i - 1][(i - 1) * 4 + 2] = -1;
        m[j + i - 1][(i - 1) * 4 + 3] = -2 * x[i - 1];
        m[j + i - 1][(i - 1) * 4 + 4] = -3 * pow(x[i - 1], 2);
    }



    // Derivadas Segundas
    j = 2 * (n - 1) + (n - 2);
    for (int i = 2; i <= n - 1; i++) {
        m[j + i - 1][(i - 1) * 4 - 3] = 0;
        m[j + i - 1][(i - 1) * 4 - 2] = 0;
        m[j + i - 1][(i - 1) * 4 - 1] = 2;
        m[j + i - 1][(i - 1) * 4] = 6 * x[i - 1];

        m[j + i - 1][(i - 1) * 4 + 1] = 0;
        m[j + i - 1][(i - 1) * 4 + 2] = 0;
        m[j + i - 1][(i - 1) * 4 + 3] = -2;
        m[j + i - 1][(i - 1) * 4 + 4] = -6 * x[i - 1];
    }

    //Condicion de Splain natural (se puede cambiar!! OJO) (recordar que aca lo estoy igualando a la derivada
    // segunda =0!!
    j = 2 * (n - 1) + (n - 2) + (n - 2);
    m[j + 1][1] = 0;
    m[j + 1][2] = 0;
    m[j + 1][3] = 2;
    m[j + 1][4] = 6 * x[0];
    b[j + 1] = 0;

    m[j + 2][N - 4] = 0;
    m[j + 2][N - 3] = 0;
    m[j + 2][N - 2] = 2;
    m[j + 2][N - 1] = 6 * x[n - 1];
    b[j + 2] = 0;

    // muevo la matriz un indice!!
    for (int i = 1; i < N; i++) {
        for (j = 1; j < N; j++) {
            m[i - 1][j - 1] = m[i][j];
        }
        b[i - 1] = b[i];
    }


    //Imprimo mi matriz
    for (int i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1; j++) {
            printf("%lf", m[i][j]);
        }

        printf("-----> %lf", b[i]);

        printf("\n");
    }

    //redefino mi N
    int Nnuevo = N - 1;
    double errorMinimo = 1e-6;
    double f;

    printf("%lf N", Nnuevo);

    //triangulacion superior
    for (int i = 0; i < Nnuevo - 1; i++) {
        //pivoteo
        int cambio = 0;
        if (fabs(m[i][i]) < errorMinimo) {
            for (int j = i + 1; j <= Nnuevo - 1; j++) {
                if (fabs(m[j][i]) > errorMinimo) {
                    for (int k = i; k <= Nnuevo - 1; k++) {
                        aux = m[i][k];
                        m[i][k] = m[j][k];
                        m[j][k] = aux;
                    }
                    aux = b[i];
                    b[i] = b[j];
                    b[j] = aux;
                    cambio = 1;
                    break;
                }
            }
            if (cambio == 0) {
                printf("El sistema es singular! no se puede resolver: %d --------m: %lf", i, m[i][i]);
                return 0;
            }
        }
        //***********************FIN PIVOTEO********************************
        for (int j = i + 1; j <= Nnuevo - 1; j++) {
            f = (-m[j][i]) / (m[i][i]);
            for (int k = i; k <= Nnuevo - 1; k++)
                m[j][k] = m[j][k] + f * m[i][k];
            b[j] = b[j] + f * b[i];
        }
    }

    //imprime la matriz como quedo!!

    printf("\nLa Matriz triangular superior quedo: \n");

    for (int i = 0; i < Nnuevo; i++) {
        for (int j = 0; j < Nnuevo; j++) {
            printf("%.2lf ", m[i][j]);
        }

        printf(" -----> %lf", b[i]);
        printf("\n");

    }


    //sustitucion regresiva
    double suma;
    double a[Nnuevo]; //vector de soluciones

    //valor de la ultima variable
    a[Nnuevo - 1] = b[Nnuevo - 1] / m[Nnuevo - 1][Nnuevo - 1];

    printf(" ------ Soluciones ----- \n");

    printf("a[%.0lf]= %lf", (double)(Nnuevo-1), a[Nnuevo-1]);

    for (int i = Nnuevo - 2; i >= 0; i--) {
        suma = b[i];
        for (int j = i + 1; j <= Nnuevo - 1; j++) {
            suma -= m[i][j] * a[j];
        }
        a[i] = (suma) / m[i][i];

        printf("\n a[%i]= %lf", i, a[i]);
    }

    printf("\n");

    //Modificacion!!
    double valorFinal;
    double delta;


    printf("Ingrese el valor a interpolar \n");
    scanf("%lf", &valor);
    //cout << "Ingrese el valor final del intervalo ";
    //cin >> valorFinal;
    //cout << "Ingrese el incremento: ";
    //cin >> delta;
    //cout<< endl;

    printf("X :         Y: \n");
    //while(valor<=valorFinal){

    for (int i = 0; i < n - 1; i++) {
        if (x[i] <= valor && valor <= x[i + 1]) {
            j = i * 4;
            resultado = a[j] + a[j + 1] * valor + a[j + 2] * pow(valor, 2) + a[j + 3] * pow(valor, 3);

            break;
        }
    }

    printf("%lf %lf", valor, resultado);
    printf("\n");
    valor += delta;
    //}
}

