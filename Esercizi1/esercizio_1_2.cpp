#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <vector>

using namespace std;

double error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n);
}   //funzione per calcolare la deviazione standard.


int main (){


   //ESERCIZIO 1.2 ----------------------------------------------------------------------------------------

   string file_p =  "Primes";
   string file_s = "seed.in";
   Random rnd(file_s, file_p);


    int M = 10000;
    int N[5]= {0, 1, 2, 10, 100};

    double lambda = 1;          // exponential distribution parameter
    double mu = 0, gamma = 1;   // Cauchy-Lorentz distribution parameters

    ofstream out_std("data/standard.csv");
    ofstream out_exp("data/exponential.csv");
    ofstream out_calo("data/cauchylorentz.csv");
    out_std << "N,extraction,value\n";
    out_exp << "N,extraction,value\n";
    out_calo << "N,extraction,value\n";

    double sum_std  = 0. ;
    double sum_exp  = 0. ;
    double sum_calo = 0. ;
    

    for(int i=0 ; i<M ; i++) {

        for (int l=1 ; l<5 ; l++) {

            for (int j=0 ; j<N[l]-N[l-1] ; j++) { //ogni volta continuo a sommare colmando il gap su N
                sum_std += rnd.Rannyu();
                sum_exp += rnd.ExpDistr( lambda);
                sum_calo += rnd.CauLorDistr( mu, gamma);

            }

            out_std << N[l] << "," << i+1 << "," << sum_std/N[l] << std::endl;
            out_exp << N[l] << "," << i+1 << "," << sum_exp/N[l] << std::endl;
            out_calo << N[l] << "," << i+1 << "," << sum_calo/N[l] << std::endl;            

        }

        sum_std = 0;
        sum_exp = 0;
        sum_calo = 0;

    }
    
   return 0;
}