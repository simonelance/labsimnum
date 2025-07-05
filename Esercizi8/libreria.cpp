#include "libreria.h"

using namespace std;
using namespace arma;

double Error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n);
}   //funzione per calcolare la deviazione standard.

double H_eval(double x, double sigma, double mu) { // calcolo valore di H*psi / psi; che è il valore di cui devo fare la media per calcolare l'integrale.
    double a = 1/(2*pow(sigma,2));
    double b = 2* a * mu ;

    return -0.5*( - 4*a*b*x*tanh(b*x) - 2*a + b*b + 4*a*a*x*x) + pow(x,4) - 2.5*x*x ;
}   //funzione per calcolare la deviazione standard.

double Boltzmann(double beta, double Hnew, double Hold){
    return exp(- beta* (Hnew-Hold));
}