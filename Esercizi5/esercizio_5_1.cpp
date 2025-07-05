#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <armadillo>
#include "metropolis.h"

#include <vector>

using namespace std;
using namespace arma;

double Error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n);
}   //funzione per calcolare la deviazione standard.


 
int main(int argc, char* argv[]){
//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 5.1    ################################################################################

//#####################################################################################################################################################################
    if(argc <3){
        cerr << " Il programma richiede in input un valore che sia <0> per simulazione con distibuzione uniforme /<1> per simulazione con distribuzione Gaussiana."<< endl;
        cerr << "\n Inoltre richiede un secondo valore <0> per orb_s , <1> per orb_p "<< endl;

        return 1;
    }
    
    int type=atoi(argv[1]);
    int orb= atoi(argv[2]);

    Metropolis metro(type, orb);
    int n_steps=1000000;
    int n_blocks= 200;
    int L= n_steps/n_blocks;

    //inizializzo la posizione da cui parte il campionamento
    double x=0., y=0., z=0.;
    metro.Initialize_pos(x,y,z);
    

    double step= 1.1 ; double prec =0.02; double target = 0.50;
    metro.SearchStep(prec, L, target, step ); // funzione per trovare uno step che permetta una frazione di valori ccettati di circa il 50%

    //Inizializzo nuovamente le posizioni che sono state mosse dal searchstep
    metro.Initialize_pos(x,y,z);


    ofstream out;
    ofstream pos_out;
    metro.OpenOutput(pos_out, out); // mi apro files di output diversi a seconda delle diverse distribuzioni dalla classe random

    vec r_ave = zeros<vec>(n_blocks);
    vec r_ave2 = zeros<vec>(n_blocks);
    vec err = zeros<vec>(n_blocks);


    for(int i=0; i<n_blocks;i++){
        double r_sum=0;
        for( int j=0; j< L; j++){

            vec v = metro.Campionamento();
            
            r_sum += norm(v,2); // posso balzare una serie di passaggi qua

            pos_out << v(0) << " " << v(1) << " " << v(2) <<  " ";  // Scrive ogni elemento della matrice
            pos_out << "\n";
        }
        if(i==0){
            r_ave(i) = r_sum/L;
            r_ave2(i) = (r_ave(i)*r_ave(i));
            err(i)= 0;
        }else{
            r_ave(i) = (r_ave(i-1) + r_sum/L)  ;
            r_ave2(i) = r_ave2(i-1) + (r_sum/L)*(r_sum/L) ;
            err(i)= Error( r_ave(i)/(i+1), r_ave2(i)/(i+1), i);
        }
        //cout << "   " << (r_ave2(i)/(i+1))-pow(r_ave(i)/(i+1),2);
        

        out << i + 1 << " " << (r_ave(i)/(i+1)) << " " << err(i) << "\n";

    }


    int n_accept = metro.Get_naccept();

    float ratio = n_accept/float(n_steps);

    

    cout << endl << "Numero di valori accettati rispetto al valore totale di campionamenti:" << ratio << endl ;
    
    pos_out.close();
    out.close();



   return 0;
}