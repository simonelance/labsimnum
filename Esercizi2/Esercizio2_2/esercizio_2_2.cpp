#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "posizione.h"
#include <vector>

using namespace std;

double Error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n);
}   //funzione per calcolare la deviazione standard.


 
int main(){
//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 2.2.1    ################################################################################

//#####################################################################################################################################################################

    string file_p =  "Primes";
    string file_s = "seed.in";
    Random rnd(file_s, file_p); // inizializzo la variabile random al di fuori di qualsiasi ciclofor in modo da evitare che questa venga ridefinita e mi ri generi gli stessi valori


    int n_trajec = 10000;
    int n_blocks = 100;
    int n_steps = 100;
    int L = n_trajec/n_blocks;      // devastante: per fare 'trova e sodstituisci' usare il comando crtl+h
    Posizione pos;
    
    double * cum_sum = new double[n_steps]();
    double * cum_sum2 = new double[n_steps]();
    double * error = new double[n_steps]();


    for(int i=0; i<n_blocks;i++){
        double * dist = new double[n_steps]();

        for(int j=0; j< L ; j++){
            pos.azzera();

            for(int k=0; k<n_steps; k++){
                
                dist[k] += (pos.get_x()*pos.get_x() + pos.get_y()*pos.get_y() + pos.get_z()*pos.get_z())/(n_trajec/n_blocks); // salvo la distanza al kesimo passo in un vettore che mi accumula sugli n_steps le distanze percorse per in ciascuna delle doverse traiettorie
                // il frazionamento per 100 serve per avere la media su 100 traiettorie
                pos.UpdatePosDiscr(rnd); // funzione che ricevendo in pasto una variabile random di fatto mi aggiorna la variabile posizione muovendola di un passo discreto in una delle direzioni in avanti o indietro.
                //cout << pos.get_x();
            }            
        }

        for(int k=0; k<n_steps; k++){
            cum_sum[k] += sqrt(dist[k]);  // dist k contiene la somma su 100 traiettorie della distanza media al k-esimo passo
            cum_sum2[k] += dist[k];

            // di fatto io uso cum_sum per accumulare i valori della distanze medie (divise per passi) una volta terminate le 100 traiettorie del i-esimo blocco
            // in questo modo poi il for dei blocchi va avanti , dist viene cancellato e ridefinito, e posso procedere con altre 100 traiettorie
            // accumulare i valori medi in cum_sum e cum2_sum mi serve perchè al termine del processo mi basterà fare un for che scorre sui passi delle mie traiettorie
            // e dividere il valore accumulato per il numero dei blocchi. In questo modo avrò tutte le info necessarie per calcolarmi valori ed errori finali.
        }
        delete[] dist;
        
    }

    for(int i=0; i<n_steps; i++){

        cum_sum[i] /= (n_blocks);
        cum_sum2[i] /= (n_blocks);

        if(i==0) {
            error[i]=0;
        }else{
            error[i] = Error(cum_sum[i], cum_sum2[i], n_blocks); // calcolo errore all'iesimo passo dopo aver trovato media e media del quadrato delle distanze
        }
    }

    ofstream out("../data/risultati2_2_1.out");
    if (!out.is_open()) {
        cerr << "Errore nell'apertura del file " << "../../data/risultati2_2_1.out" << endl;
        return 1;
    }
    out << "n_step r error" << endl;
    cout << "writing 3d discrete random walk data to file " << "../../data/risultati2_2_1.out" << endl;
    for(int i=0; i<n_steps; i++){
        out << i << " " << cum_sum[i] << " " << error[i] <<  endl;
    }
    out.close();


    delete[] cum_sum;
    delete[] cum_sum2;
    delete[] error;

//#####################################################################################################################################################################

//##############################################################    ESERCIZIO 2.2.2    ################################################################################

//#####################################################################################################################################################################

    Posizione poscont;
    
    cum_sum = new double[n_steps]();
    cum_sum2 = new double[n_steps]();
    error = new double[n_steps]();


    for(int i=0; i<n_blocks;i++){
        double * dist = new double[n_steps]();

        for(int j=0; j< L ; j++){
            poscont.azzera();

            for(int k=0; k<n_steps; k++){
                
                dist[k] += (poscont.get_x()*poscont.get_x() + poscont.get_y()*poscont.get_y() + poscont.get_z()*poscont.get_z())/(n_trajec/n_blocks); // salvo la distanza al kesimo passo in un vettore che mi accumula sugli n_steps le distanze percorse per in ciascuna delle doverse traiettorie
                // il frazionamento per 100 serve per avere la media su 100 traiettorie
                poscont.UpdatePosCont(rnd); // funzione che ricevendo in pasto una variabile random di fatto mi aggiorna la variabile posizione muovendola di un passo discreto in una delle direzioni in avanti o indietro.
                //cout << poscont.get_x();
            }            
        }

        for(int k=0; k<n_steps; k++){
            cum_sum[k] += sqrt(dist[k]);  // dist k contiene la somma su 100 traiettorie della distanza media al k-esimo passo
            cum_sum2[k] += dist[k];

            // il processo è lo stesso di prima, semplicemente ora uso un metodo diverso, basato sulle sferiche, per incrementare la posizione.
        }
        delete[] dist;
        
    }

    for(int i=0; i<n_steps; i++){
        cum_sum[i] /= (n_blocks);
        cum_sum2[i] /= (n_blocks);



        if(i==0) {
            error[i]=0;
        }else{
            error[i] = Error(cum_sum[i], cum_sum2[i], n_blocks); // calcolo errore all'iesimo passo dopo aver trovato media e media del quadrato delle distanze
        }
    }

    ofstream out2("../data/risultati2_2_2.out");
    if (!out2.is_open()) {
        cerr << "Errore nell'apertura del file " << "../../data/risultati2_2_2.out" << endl;
        return 1;
    }
    out2 << "n_step r error" << endl;
    cout << "writing 3d discrete random walk data to file " << "../../data/risultati2_2_2.out" << endl;
    for(int i=0; i<n_steps; i++){
        out2 << i << " " << cum_sum[i] << " " << error[i] <<  endl;
    }
    out2.close();


    delete[] cum_sum;
    delete[] cum_sum2;
    delete[] error;


   return 0;
}