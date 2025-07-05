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

double Evaluate(double r) {// voglio calcolare  il valore da integrare: non 
    
    return ((cos( r * (M_PI/2)) *(M_PI/2)) /  (2-2*r)) ; //funzione 
}   



 
int main (int argc, char *argv[]){


   //ESERCIZIO 2.1 ----------------------------------------------------------------------------------------

   string file_p =  "Primes";
   string file_s = "seed.in";
   Random rnd(file_s, file_p);


    int M = 10000;
    int N= 100;
    int L= M/N;


    double *r= new double [M]; for(int i=0; i<M; i++) r[i]= rnd.Rannyu(); // carico i 100000 numeri random generated
    double *x= new double [N]; for(int i=0; i<N; i++) x[i]=i;
    double *ave= new double [N];
    double *av2= new double [N];
    double *sum_prog= new double [N];
    double *su2_prog= new double [N];
    double *err_prog= new double [N];


    for(int i=0; i<N; i++) {ave[i]=0; av2[i]=0; sum_prog[i]=0; su2_prog[i]=0; err_prog[i]=0;}

    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi
        double sum = 0;

        for (int j = 0; j < L; ++j) {
            int k = j + i * L;        // faccio numero di blocchi i* numero di elementi in ciascun blocco, e ci sommo j, ovvero il numero dell'elemento del blocco attuale a cui sono arrivato
            sum += cos(r[k] * (M_PI/2)) *(M_PI/2) ;      // Valuto il valore random generato tra 0-1 e lo valuto con la funzione adeguata. nella variabile sum sommo ricorsivamente tutti questi valori in modo da calcolarne poi la media per l'iesimo blocco
        }

        ave[i] = sum / L;             // Alla fine di ogni blocco prendo la soma totale e la divido per il numero di tiri in quel blocco facendo la deviazione standard media su quel set di tiri.
        av2[i] = (ave[i]) * (ave[i]); // faccio il quadrato dei valori medi di ciascun blocco

        
    }

    ofstream risultati1("../data/risultati_2_1_1.out");
    risultati1 << "Block,Integral,Value2,Error\n";

    if(risultati1.is_open()){
        cout << endl << "File risultati_2_1_1.out aperto correttamente"<< endl;
    } else cerr << endl <<"Errore in apertura del file risultati_2_1_1.out"<< endl; 
    
    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi

        for(int j=0; j < (i+1) ; j++){
            sum_prog[i] += ave[j]; // sto costruendo la cumulativa della deviazione std calcolarta con l for precedente, 
            su2_prog[i] += av2[j]; // e la cumulativa del quadrato di essa in modo da poter poi calcolare l'errore sul integrale 
        }

        sum_prog[i]= sum_prog[i] / (i+1); // MEDIA cumulativa per tutti i blocchi fino all'iesimo
        su2_prog[i]= su2_prog[i] / (i+1); // media cumulativa del quadrato delle medie sui primi i+1 blocchi (i+1 perchè il primo blocco ha indice 0)
        err_prog[i]= error(sum_prog[i], su2_prog[i], i); //di fatto qua mi calcolo l'errore sulla deviazione standard. cioe sto facendo la deviazione standar utilizzando media e media quadra CUMULATIVE fino all'iesimo passo
        risultati1 << i + 1 << "," << sum_prog[i]  << "," << su2_prog[i] << "," << err_prog[i] << "\n";
    }

    risultati1.close();

// punto 2-----------------------------------------------------------------------------------------------------------------------
    for(int i=0; i<N; i++) {ave[i]=0; av2[i]=0; sum_prog[i]=0; su2_prog[i]=0; err_prog[i]=0;}
    for(int i=0; i<M; i++) r[i]= rnd.DistribCos(); // sto caricando su r i valori distribuiti secondo la distibuzione di probabilita prescelta per migliorare e ediminuire incertezza
    // in realtà x ci va bene così: è il numero di lanci per ogni blocco 

    for (int i = 0; i < N; ++i) {        //itero sul numero dei blocchi
        double sum = 0;

        for (int j = 0; j < L; ++j) {
            int k = j + i * L;           // faccio numero di blocchi i* numero di elementi in ciascun blocco, e ci sommo j, ovvero il numero dell'elemento del blocco attuale a cui sono arrivato
            sum += Evaluate(r[k]) ;      // Valuto il valore random generato tra 0-1 e lo valuto con la funzione adeguata. nella variabile sum sommo ricorsivamente tutti questi valori in modo da calcolarne poi la media per l'iesimo blocco
        }

        ave[i] = sum / L;                // Alla fine di ogni blocco prendo la soma totale e la divido per il numero di tiri in quel blocco facendo la deviazione standard media su quel set di tiri.
        av2[i] = (ave[i]) * (ave[i]);    // faccio il quadrato dei valori medi di ciascun blocco
    }

    ofstream risultati2("../data/risultati_2_1_2.out");
    risultati2 << "Block,Integral,Value2,Error\n";

    if(risultati2.is_open()){
        cout << endl << "File risultati_2_1_2.out aperto correttamente"<< endl;
    } else cerr << endl <<"Errore in apertura del file risultati_2_1_2.out"<< endl; 
    
    for (int i = 0; i < N; ++i) {   //itero sul numero dei blocchi

        for(int j=0; j < (i+1) ; j++){
            sum_prog[i] += ave[j];  // sto costruendo la cumulativa della deviazione std calcolarta con l for precedente, 
            su2_prog[i] += av2[j];  // e la cumulativa del quadrato di essa in modo da poter poi calcolare l'errore sul integrale 
        }

        sum_prog[i]= sum_prog[i] / (i+1); // MEDIA cumulativa per tutti i blocchi fino all'iesimo
        su2_prog[i]= su2_prog[i] / (i+1); // media cumulativa del quadrato delle medie sui primi i+1 blocchi (i+1 perchè il primo blocco ha indice 0)
        err_prog[i]= error(sum_prog[i], su2_prog[i], i); //di fatto qua mi calcolo l'errore sulla deviazione standard. cioe sto facendo la deviazione standar utilizzando media e media quadra CUMULATIVE fino all'iesimo passo
        risultati2 << i + 1 << "," << (sum_prog[i]) << "," << su2_prog[i] << "," << err_prog[i] << "\n";
    }

    risultati2.close();



    delete[] r;
    delete[] x;
    delete[] ave;
    delete[] av2;
    delete[] sum_prog;
    delete[] su2_prog;
    delete[] err_prog;

   rnd.SaveSeed();
   return 0;
}