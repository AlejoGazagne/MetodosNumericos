#include <iostream>
#include <cmath>

using namespace std;

// double f(double x) { return log(x)+exp(sin(x))-x; }
double f(double x){ return pow(x, 10) - 1; }
// double f(double x) { return ((9.81*x)/14)*(1-exp(-(14/x)*7))-35; }

int main(){
    double a, b, cv, cn, e, t, ep;
    int cont = 1;
    printf("Ingrese el valor de a: ");
    scanf("%lf", &a);
    printf("Ingresa el valor de b: ");
    scanf("%lf", &b);

    t = pow(10,-5);
    cn = (f(b)*a-f(a)*b)/(f(b)-f(a));
    cv = a;
    e = fabs(cn - cv);

    if(f(a)*f(b) > 0){
        printf("No hay interseccion con el eje x en el intervalo dado. \n");
        return 0;
    }

    do{
        if(f(a)*f(cn) < 0) b = cn;
        else if(f(b)*f(cn) < 0) a = cn;
        else break;

        cv = cn;
        cn = (f(b)*a-f(a)*b)/(f(b)-f(a));
        e = fabs(cn - cv);
        //ep = fabs((cn-cv)/cn)*100;
        cont++;

    } while(e > t);

    printf("\nResultados Regula Falsi:\n");
    printf("El valor de la raiz es %.12lf con error de %.12lf\n", cn, e);
    printf("La funcion evaluada en la raiz es igual a: %lf\n", f(cn));
    printf("Iteracion: %d \n", cont);

    return 0;
}