#include <iostream>
#include <cmath>

using namespace std;

//double f(double x) { return -2 + 7*x - 5*pow(x, 2) + 6*pow(x, 3); }
double f(double x) { return -15.3315 + 58.6035793651*x -74.2201984127*x*x + 30.9503968254*pow(x, 3); }
// double f(double x) { return exp(-x) - x; }
// double f(double x) { return ((9.81*x)/14)*(1-exp(-(14/x)*7))-35; }
// double f(double x) { return ((log(x)-(1.-(1./x)))/(log(x)+((1.-(1./x))/(2./3.))))- 0.3; }
//double f(double x) {return ((9.81*(68.1))/x)*(1 - exp((-x/68.1)*10))-40.100; }
//double f(double x) { return -15.3315+58.6036*x-74.2202*pow(x,2)+30.9504*pow(x,3); }

int main(){
    double a, b, cv, cn, e, t, ep;
    int cont = 0;
    printf("Ingrese el valor de a: ");
    scanf("%lf", &a);
    printf("Ingresa el valor de b: ");
    scanf("%lf", &b);
    t = pow(10,-8);
    double ai = a, bi = b;

    if(f(a)*f(b) > 0){
        printf("No hay interseccion con el eje x en el intervalo dado. \n");
        return 0;
    }

    do{
        cn = (a + b)/2.0;
        cv = a;
        e = fabs(cn - cv);
        ep = fabs((cn-cv)/cn)*100;

        if(f(a)*f(cn) < 0) b = cn;
        else if(f(b)*f(cn) < 0) a = cn;
        else break;
        cont++;
    } while(e > t);

    printf("\nResultados Biseccion:\n");
    printf("El valor de la raiz es %lf\nError aproximado de %lf\n", cn, e);
    printf("Error porcentual %lf\n", ep);
    printf("La funcion evaluada en la raiz es igual a: %lf\n", f(cn));
    printf("La cantidad de iteraciones debe ser aproximadamente: %lf \n", log2((bi-ai)/e));
    printf("Iteracion: %d \n", cont);

    return 0;
}