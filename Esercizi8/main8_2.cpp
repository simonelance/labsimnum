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

void PrintProgressBar(int current, int total, int barWidth = 50) {
    float progress = float(current) / total;
    int pos = barWidth * progress;

    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
}
 
int main(int argc, char* argv[]){
//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 8.2    ################################################################################

//#####################################################################################################################################################################
// SIMULATED ANNEALING PER OTTENERE UN VALORE DI <H> CHE CONVERGA VERSO IL GROUND STATE MUOVENDOSI NELLO SPAZIO DEI PARAMETRI sigma e mu ED AGGIORNANDOLI OGNI VOLTA CHE ABBASSO LA TEMPERATURA

    Metropolis metro;
    int n_steps=5000;
    int n_blocks= 100;
    int n_temp= 1000;
    double sigma= 1.; // valori di partenza dei parametri con cui si parte per il simulated annealing
    double mu= 1.;
    double mu_old = mu, sigma_old = sigma;
    double delta_mu = 0.5, delta_sigma = 0.5;
    double d_mu, d_sigma;
    double B=0.0;
    double T0=1.;
    Random rnd;
    double Hnew, Hold;

    double step= 1. ; double prec = 0.02; double target = 0.5;
    metro.SearchStep(prec, 10000, target, step ); // funzione per trovare uno step  di campionamento psi che permetta una frazione di valori ccettati di circa il 50%

    sigma= 1.;
    mu= 1.;
// APERTURA FILES DI OUTPUT
    ofstream out;
    ofstream pos_out;
    ofstream out8_2;
    metro.OpenOutput(pos_out, out, out8_2); 

    //ognuno di questi vettori immagazzinerà i valori dell'integrale in funzione del numero di blocchi: dopo che la funzione Integral avrà aggiornato le variabili private,
    //io andro ad usare i metodi get per aggiornare le variabili del mio main.
    vec H_ave = zeros<vec>(n_blocks);
    vec err = zeros<vec>(n_blocks);

    for(int i=0; i<n_temp;i++){///-------oda sistemare

        PrintProgressBar(i + 1, n_temp);
        B = double(i+1);
        double T = 1./B;

        d_mu = d_mu > mu_old ? mu_old : delta_mu;
        d_sigma = d_sigma > sigma_old ? sigma_old : delta_sigma;

        // Step gaussiani la cui varianza diminuice , ovvero si avvicinano attorno a 0 man mano che la temperatura cresce e ho bisogno di una ricerca più fine.
        mu = fabs(mu_old + rnd.Gauss(0.,d_mu*T/T0));
        sigma = fabs(sigma_old + rnd.Gauss(0.,d_sigma*T/T0));
        
        metro.SetParam( sigma, mu); // setto i nuovi parametri

        metro.Integral_BA( n_blocks, n_steps); //è una fz void che aggiorna le variabili private -> ho controllato che funzioni ed ho risolto i problemi, a sto point probabilmente si tratta di come aggiorno i valori di sigma e mu
         
        H_ave = metro.get_H_ave(); // abbiamo il vettore che immagazzina i valori del data blocking per ciascuna temperatura diversa. Ultimo valore con relativo errore è quello che guardo
        err = metro.get_H_err();

        if (i==0) Hold = H_ave(n_blocks-1);
        Hnew= H_ave(n_blocks-1);

        double alpha= fmin(1, (Boltzmann( B, Hnew, Hold)));

        double r = rnd.Rannyu() ;
        if( r <= alpha ){
            //n_accept ++;
            Hold = Hnew; // se il valore è accettato salvo nell xold questo valore in modo da poter nuovamente aggiornare _x nel nuovo passo e paragonarlo alla sua versione precedente
            mu_old = mu;
            sigma_old = sigma;
        }
        else{
            Hnew= Hold;// altrimenti riazzero il passo e riprovo ad aggiornarlo con un altro numero casuale
            mu= mu_old;
            sigma= sigma_old;
        }


        // STAMPO SUL FILE: TEMP - SIGMA - MU - <H> - H_ERR
        out8_2 << i+1<< " " <<  T << " " << sigma <<" " << abs(mu) <<" " << Hnew << " " << err(n_blocks-1) << endl;
        

        
    }

    int n_accept = metro.Get_naccept();
    float ratio = n_accept/float(n_steps* n_temp * n_blocks);

    cout << endl << "Numero di valori accettati rispetto al valore totale di campionamenti della funzione d'onda:" << ratio << endl ;
    //questo rapporto non centra con il simulated annealing: ma siolamente con i valori di psi campionati tramite metropolis
    
    pos_out.close();
    out.close();
    out8_2.close();



   return 0;
}


//HO VOLUTO IMPLEMENTARE LA BLOCKING AVERAGE PER CALCOLARE IL VALORE DELL INTEGRALE (OVVERO IL VAL MEDIO DELL'HAMILTONIANA), ALL'INTERNO DELLA CLASSE METROPOLIS
//IN QUESTO MODO POSSO CHIAMARE SEMPLICEMENTE LA FUNZIONE INTEGRAL PER CIASCUNA TEMPERATURA DIVERSA SENZA DOVER SCRIVERE NEL MAIN UN DOPPIO FOR SCOMODO
/*
for(int i=0; i<n_blocks;i++){
            double r_sum=0;
            for( int j=0; j< L; j++){

                double x = metro.Campionamento();
                double H_temp = H_eval( x, sigma, mu );

                r_sum += H_temp; 
                pos_out << x <<  " ";  
                pos_out << "\n";
            }
            if(i==0){
                r_ave(i) = r_sum/L; // nel nuovo elemento del vettore salvo la somma dei valori che mi interessano
                r_ave2(i) = (r_ave(i)*r_ave(i));
                err(i)= 0;
            }else{
                r_ave(i) = (r_ave(i-1) + r_sum/L)  ;
                r_ave2(i) = r_ave2(i-1) + (r_sum/L)*(r_sum/L) ;
                err(i)= Error( r_ave(i)/(i+1), r_ave2(i)/(i+1), i);
            }
            //cout << "   " << (r_ave2(i)/(i+1))-pow(r_ave(i)/(i+1),2);


            out << i + 1 << " " << (r_ave(i)/(i+1)) << " " << err(i) << "\n";

        }*/
