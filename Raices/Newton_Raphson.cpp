#include <iostream>
#include <cmath>

// double f(double x){ return 4*pow(x,3)-52*pow(x,2)+160*x-100; }
// double fp(double x) { return 12*pow(x,2)-104*x+160; }

double f(double x){ return 2*x+log10(x)- sin(3*x); }
double fp(double x){ return 2+(1/(x*log(10)))- cos(3*x)*3; }

int main(){
    double e, t, cv, cn;
    int cont = 0;
    printf("Ingrese un valor inicial: ");
    scanf("%le", &cv);
    t = pow(10, -6);

    do{
        cont++;
        //double lim = (f(cv + 0.01)- f(cv))/(2*0.01);
        double lim = (3*f(cv)-4*f(cv-0.01)+f(cv-(2*0.01)))/(2*0.01);
        if(fabs(lim) < 0.01){
            printf("No se cumple el criterio de convergencia \n");
             printf("El metodo diverge (|f'(x)| cercano a 0)");
            return 0;
        }
        /*if(fabs(fp(cv)) < 0.0001){
            printf("No se cumple el criterio de convergencia \n");
            return 0;
        }*/

        cn = cv - f(cv)/fp(cv);
        e = fabs(cn - cv);
        cv = cn;
    } while(e > t || cont > 10000);

    printf("El valor de la raiz es %lf con error de %.12lf \n", cn, e);
    printf("La funcion evaluada en la raiz es igual a: %lf\n", f(cn));
    printf("Iteracion: %d \n", cont);


    return 0;
}
// no entiendo del todo las restricciones