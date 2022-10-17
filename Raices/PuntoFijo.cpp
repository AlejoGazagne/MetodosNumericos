#include <iostream>
#include <cmath>

double f(double x) { return cos(sin(x))+x; }

//double f(double x) { return 3*x + sin(x) - exp(x) + x; }
//double g(double x) { return 3 + cos(x) - exp(x); }

int main(){
    double e, t, cv, cn;
    int cont = 0;
    printf("Ingrese un valor inicial: ");
    scanf("%lf", &cv);
    t = pow(10, -6);

    do{
        cont++;
        double lim = (f(cv + 0.001) - f(cv))/(0.001);
        // double lim = (3*f(cv)-4*f(cv-0.01)+f(cv-(2*0.01)))/(2*0.01);
        if(fabs(lim) >= 1){
            printf("No se cumple el criterio de convergencia \n");
            printf("El metodo diverge (|g'(x)|>1)\n");
            return 0;
        }
        cn = f(cv);
        e = fabs(cn - cv);
        cv = cn;
    } while (e > t);

    printf("\nResultados Punto Fijo:\n");
    printf("El valor de la raiz es %lf con error de %.12lf \n", cn, e);
    printf("La funcion evaluada en la raiz es igual a: %lf\n", f(cn));
    printf("Iteracion: %d \n", cont);

    return 0;
}