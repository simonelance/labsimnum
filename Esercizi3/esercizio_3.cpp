#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "GBM.h"
#include <vector>

using namespace std;

double Error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n); // l'errore dovrebbe essere calcolato con a denominatore n-1; tuttavia essendo la funzione dentro un for. io dividerò per il valore i dell'iterazione che sarà già la n-1 esima componente del vettore
}   //funzione per calcolare la deviazione standard.


 
int main(int argc, char* argv[]){
//#####################################################################################################################################################################
//##############################################################    ESERCIZIO 3.1    ##################################################################################
//#####################################################################################################################################################################
    if(argc !=2){cerr<< "Inserire <n_step> oltre ad " << argv[0] <<" !" << endl << " valori di n_step richiesti: <1> / <100> \n"; return 1;}
    
    int n_step = atoi(argv[1]);

    int M = 10000; // numero di prezzi da generare, che andranno poi divisi nei vari blocchi
    int n_blocks = 100;
    int L = M/n_blocks;      // numero di estrazioni del prezzo St in ogni blocco con conseguente valore della call opt/ put opt

    double T=1.; // tempo finale
    double S0=100.; // prezzo al tempo t=0
    double k=100.; //
    double sigma=0.25; //volatilità
    double r=0.1; //drift
    GBM gbm(S0,r,sigma,k,T);
    
    double * Ci_ave = new double[n_blocks]();
    double * Ci_ave2 = new double[n_blocks]();
    double * C_error = new double[n_blocks]();
    double * C_cum_sum = new double[n_blocks]();
    double * C_cum_sum2 = new double[n_blocks]();

    double * Pi_ave = new double[n_blocks]();
    double * Pi_ave2 = new double[n_blocks]();
    double * P_cum_sum = new double[n_blocks]();
    double * P_cum_sum2 = new double[n_blocks]();
    double * P_error = new double[n_blocks]();



    for(int i=0; i<n_blocks;i++){
        double Ci_sum= 0;
        double Pi_sum= 0;
        for(int j=0; j< L ; j++){
            double St= gbm.Price(n_step);
            Ci_sum += exp(-r*T) * max(0., St-k);  //accumulo i valori di profitto della call option al tempo T dopo aver generato un valore di St che segue il moto browniano geometrico 
            Pi_sum += exp(-r*T) * max(0., k-St);

        }
        
        Ci_ave[i]= Ci_sum/L;   // All'interno dell'i-esimo blocco ho otten L valori di Ci che ho accumulato, vado ad ottenerne la media
        Ci_ave2[i]= Ci_ave[i]*Ci_ave[i];        

        Pi_ave[i]= Pi_sum/L;   // All'interno dell'i-esimo blocco ho otten L valori di Ci che ho accumulato, vado ad ottenerne la media
        Pi_ave2[i]= Pi_ave[i]*Pi_ave[i];  
        
    }

    //qua fuori dovro fare un nuovo doppio for per calcolare l'errore progressivo in funzione dei blocchi oltre 
    for( int i=0; i< n_blocks; i++){
        for( int j=0; j<(i+1); j++){
            C_cum_sum[i] += Ci_ave[j]; // accumulo i valori delle medie per tutti i modi fino all'iesimo in modo da poi fare una nuova media su di essi al di fuori del for
            C_cum_sum2[i] += Ci_ave2[j]; // idem per il quadrato delle medie per ciascun blocco
            
            P_cum_sum[i] += Pi_ave[j]; // accumulo i valori delle medie per tutti i modi fino all'iesimo in modo da poi fare una nuova media su di essi al di fuori del for
            P_cum_sum2[i] += Pi_ave2[j]; // idem per il quadrato delle medie per ciascun blocco
            
        }
        
        C_cum_sum[i] /= (i+1); // arrivando fino all'iesimo blocco otteniamo questi valori come miglior stima della media e l'errore sottostante che migliora
        C_cum_sum2[i] /= (i+1);// man mano che aumentiamo i blocchi su cui lavoriamo
        
        P_cum_sum[i] /= (i+1);
        P_cum_sum2[i] /= (i+1);

        C_error[i] = Error( C_cum_sum[i], C_cum_sum2[i], i); 
        P_error[i] = Error( P_cum_sum[i], P_cum_sum2[i], i); 

    }

//STAMPO TUTTO SU FILE NELL'APPOSITA CARTELLA
    if(n_step ==1){ofstream out("../data/risultati3_1.out");
        if (!out.is_open()) {
        cerr << "Errore nell'apertura del file " << "../data/risultati3_1.out" << endl;
        return 1;
        }
        out << "n_step Call_profit Call_err Put_profit Put_err" << endl;
        cout << "Stampo i valori del Profitto per Call Option e Put Option " << "../data/risultati3_1.out" << endl;
        for(int i=0; i<n_blocks; i++){
        out << (i+1) << " " << C_cum_sum[i] << " "  << C_error[i] << " " <<  P_cum_sum[i] << " " << P_error[i] << endl; // mi salvo i risultati di Ci e i relativi errori in funzione del numero di blocchi usati per calcolare media ed errore
        }
        out.close();}
    else{
        ofstream out1("../data/risultati3_2.out"); // nello stesso file ho stampato sia call_opt che put_opt indirette
        if (!out1.is_open()) {
        cerr << "Errore nell'apertura del file " << "../data/risultati3_2.out" << endl;
        return 1;
        }
        out1 << "n_step Call_profit Call_err Put_profit Put_err" << endl;
        cout << "Stampo i valori del Profitto per Call Option e Put Option " << "../data/risultati3_2.out" << endl;
        for(int i=0; i<n_blocks; i++){
        out1 << (i+1) << " " << C_cum_sum[i] << " "  << C_error[i] << " " <<  P_cum_sum[i] << " " << P_error[i] << endl; // mi salvo i risultati di Ci e i relativi errori in funzione del numero di blocchi usati per calcolare media ed errore
        }
        out1.close();
    }


    delete[] C_cum_sum;
    delete[] C_cum_sum2;
    delete[] C_error;
    delete[] Ci_ave2;
    delete[] Ci_ave;

    delete[] Pi_ave2;
    delete[] Pi_ave;
    delete[] P_cum_sum;
    delete[] P_cum_sum2;
    delete[] P_error;

//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 3.2    ##################################################################################

//#####################################################################################################################################################################


   return 0;
}