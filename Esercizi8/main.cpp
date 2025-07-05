#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <armadillo>
#include "metropolis.h"
#include "libreria.h"

#include <vector>

using namespace std;
using namespace arma;


 
int main(int argc, char* argv[]){
//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 8.1    ################################################################################

//#####################################################################################################################################################################
// ci sta far si che la classe metropolis prenda in input la funzione con cui dovrà calcolare le probabilità per aggiornare le configurazioni

    Metropolis metro;
    int n_steps=500000;
    int n_blocks= 100;
    int L= n_steps/n_blocks;
    double sigma= 0.5;
    double mu= 1. ;
    Random rnd;
    metro.SetParam( sigma, mu); // setto i nuovi parametri


    double step= 1. ; double prec = 0.05; double target = 0.5;
    metro.SearchStep(prec, L, target, step ); // funzione per trovare uno step che permetta una frazione di valori ccettati di circa il 50%

    ofstream out;
    ofstream pos_out;
    metro.OpenOutput(pos_out, out); // mi apro files di output diversi a seconda delle diverse distribuzioni dalla classe random

    vec h_ave = zeros<vec>(n_blocks);
    vec h_ave2 = zeros<vec>(n_blocks);
    vec err = zeros<vec>(n_blocks);



    for(int i=0; i<n_blocks;i++){
        double h_sum=0;
        for( int j=0; j< L; j++){
            double x = metro.Campionamento();
            double H_temp = H_eval( x, sigma, mu );
            h_sum += H_temp; 
            pos_out << x <<  " ";  
            pos_out << "\n";
        }
        if(i==0){
            h_ave(i) = h_sum/L; // nel nuovo elemento del vettore salvo la somma dei valori che mi interessano
            h_ave2(i) = (h_ave(i)*h_ave(i));
            err(i)= 0;
        }else{
            h_ave(i) = (h_ave(i-1) + h_sum/L)  ;
            h_ave2(i) = h_ave2(i-1) + (h_sum/L)*(h_sum/L) ;
            err(i)= Error( h_ave(i)/(i+1), h_ave2(i)/(i+1), i);
        }
        //cout << "   " << (h_ave2(i)/(i+1))-pow(h_ave(i)/(i+1),2);
        out << i + 1 << " " << (h_ave(i)/(i+1)) << " " << err(i) << "\n";
    }


    int n_accept = metro.Get_naccept();

    float ratio = n_accept/float(n_steps);

    

    cout << endl << "Numero di valori accettati rispetto al valore totale di campionamenti:" << ratio << endl ;
    
    pos_out.close();
    out.close();



   return 0;
}


