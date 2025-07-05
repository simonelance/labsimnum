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

double chi_2(int *counter , int M, int L) {
    double chi2 =0;
    double p = double(L/M);
    for(int i=0; i<M; i++){
        chi2 +=( (counter[i] - p) * (counter[i] - p) / p);
    }
    //cout <<"chi2----- "<< chi2<< endl;
    return chi2;
}
 
int main (int argc, char *argv[]){


   //ESERCIZIO 1.1 ----------------------------------------------------------------------------------------

   string file_p =  "Primes";
   string file_s = "seed.in";
   Random rnd(file_s, file_p);


    int M = 1000000;
    int N=100;
    int L= M/N;


    double *r= new double [M]; for(int i=0; i<M; i++) r[i]= rnd.Rannyu();
    double *x= new double [N]; for(int i=0; i<N; i++) x[i]=i;
    double *ave= new double [N];
    double *av2= new double [N];
    double *sum_prog= new double [N];
    double *su2_prog= new double [N];
    double *err_prog= new double [N];

    for(int i=0; i<N; i++) {ave[i]=0; av2[i]=0; sum_prog[i]=0; su2_prog[i]=0; err_prog[i]=0;}

    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi
        double sum1 = 0;

        for (int j = 0; j < L; ++j) {
            int k = j + i * L; // faccio numero di blocchi i* numero di elementi in ciascun blocco, e ci sommo j, ovvero il numero dell'elemento del blocco attuale a cui sono arrivato
            sum1 += r[k];            // Somma dei numeri casuali
        }

        ave[i] = sum1 / L;            // Media r_i, essendo che sommo su i che va da 0 a N-1 ottengo N valori, ovvero uno per ciascun numero dei blocchi
        av2[i] = (ave[i]) * (ave[i]); // faccio il quadrato dei valori medi di ciascun blocco
    }
    
    ofstream risultati("data/risultati_1_1_1.out");

    if(risultati.is_open()){
        cout << endl << "File risultati_1_1.out aperto correttamente"<< endl;
        risultati << "Block,prog_val,prog_val2,error\n";


    } else cerr << endl <<"Errore in apertura del file risultati.out"<< endl; 
    
    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi

        for(int j=0; j < (i+1) ; j++){
            sum_prog[i] += ave[j];
            su2_prog[i] += av2[j];
        }

        sum_prog[i]= sum_prog[i] / (i+1); // media cumulativa per tutti i blocchi fino all'iesimo
        su2_prog[i]= su2_prog[i] / (i+1); // media cumulativa del quadrato delle medie sui primi i+1 blocchi (i+1 perchè il primo blocco ha indice 0)
        err_prog[i]= error(sum_prog[i], su2_prog[i], i);
        risultati << i + 1 << "," << (sum_prog[i]) << "," << su2_prog[i] << "," << err_prog[i] << "\n";
    }


    //ESERCIZIO 1.1.2-------------------------------------------------------------------------------------------------------------------
    
    for(int i=0; i<N; i++) {ave[i]=0; av2[i]=0; sum_prog[i]=0; su2_prog[i]=0; err_prog[i]=0;}


    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi
        double sum = 0;
        for (int j = 0; j < L; ++j) {
            int k = j + i * L; // faccio numero di blocchi i* numero di elementi in ciascun blocco, e ci sommo j, ovvero il numero dell'elemento del blocco attuale a cui sono arrivato
            sum += (r[k] -0.5)*(r[k] -0.5);            // Somma cumulativa dei numeri casuali meno la media in modod da fare l'integrale della deviazione std, 
        }

        ave[i] = sum / L;            // Alla fine di ogni blocco prendo la soma totale e la divido per il numero di tiri in quel blocco facendo la deviazione standard media su quel set di tiri.
        av2[i] = (ave[i]) * (ave[i]); // faccio il quadrato dei valori medi di ciascun blocco
    }
    

    ofstream risultati2("data/risultati_1_1_2.out");

    if(risultati2.is_open()){
        cout << endl << "File risultati_1_1_2.out aperto correttamente"<< endl;
        risultati2 << "Block,prog_val,prog_val2,error\n";

    } else cerr << endl <<"Errore in apertura del file risultati_1_1_2.out"<< endl; 
    
    for (int i = 0; i < N; ++i) { //itero sul numero dei blocchi

        for(int j=0; j < (i+1) ; j++){
            sum_prog[i] += ave[j]; // sto costruendo la cumulativa della deviazione std calcolarta con l for precedente, 
            su2_prog[i] += av2[j]; // e la cumulativa del quadrato di essa in modo da poter poi calcolare l'errore sul integrale della deviazione standard
        }

        sum_prog[i]= sum_prog[i] / (i+1); // media cumulativa per tutti i blocchi fino all'iesimo
        su2_prog[i]= su2_prog[i] / (i+1); // media cumulativa del quadrato delle medie sui primi i+1 blocchi (i+1 perchè il primo blocco ha indice 0)
        err_prog[i]= error(sum_prog[i], su2_prog[i], i); //di fatto qua mi calcolo l'errore sulla deviazione standard. cioe sto facendo la deviazio
        risultati2 << i + 1 << "," << (sum_prog[i] ) << "," << su2_prog[i] << "," << err_prog[i] << "\n";
    }


//ESERCIZIO 1.1.3-------------------------------------------------------------------------------------------------------------------
    
    for(int i=0; i<N; i++) {ave[i]=0; av2[i]=0; sum_prog[i]=0; su2_prog[i]=0; err_prog[i]=0;}
    
    M = 100;
    L = 10000;
    double bin_size = 1./100. ;
    
    cout << "Bin_size = " << bin_size<< endl << endl;
    int nblk=1000;
    double *chi2 = new double [nblk]; 
    

    for (int i = 0; i < nblk; ++i) { //itero sul numero dei blocchi
        int *counter= new int [M]();

        for (int j = 0; j < L; ++j) {
            double a = rnd.Rannyu();
            int bin = int(a/bin_size);
            //cout << "bin = " << bin << endl;
            counter[bin] ++;

        }
        chi2[i]= chi_2(counter , M, L);
        delete[] counter;
    }
    cout << "fin qua ci siamo" << endl ;
    ofstream risultati3;
    if(nblk==100){
    risultati3.open("data/risultati_1_1_3.out");
    }else if(nblk==1000){risultati3.open("data/risultati_1_1_3_1000values.out");}
    else cout << endl << "Error : unknown nblk number!" << endl ;
    risultati3 << "N,Chi2_value\n";

    if(risultati3.is_open()){
        cout << endl << "File risultati_1_1_3.out aperto correttamente"<< endl;
    } else cerr << endl <<"Errore in apertura del file risultati_1_1_2.out"<< endl; 
    
    for (int i = 0; i < nblk; ++i) { //itero sul numero dei blocchi
        risultati3 << i+1 << "," << chi2[i] << "\n";
    }



    risultati.close();
    risultati2.close();
    risultati3.close();

    delete[] chi2;
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