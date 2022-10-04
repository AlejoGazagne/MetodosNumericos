#include <iostream>
#include <cmath>

double f(double x){ return exp(-x)-x; }

int main(){
    double cn, e,t, cv, cvv;
    int cont = 0;
    printf("Ingrese un valor inicial: ");
    scanf("%le", &cv);
    printf("Ingrese otro valor: ");
    scanf("%le", &cvv);
    t = pow(10, -5);

    do{
        cont++;
        cn = cv - (f(cv)*(cvv - cv))/(f(cvv) - f(cv));
        e = fabs(cn - cv);
        cvv = cv;
        cv = cn;
    } while (e > t|| cont > 5000);

    printf("El valor de la raiz es %lf con error de %lf \n", cn, e);
    printf("La funcion evaluada en la raiz es igual a: %lf\n", f(cn));
    printf("Iteracion: %d \n", cont);

    return 0;
}