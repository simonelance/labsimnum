/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in"); // apro il file seed in e carico sul vettore seed i 4 valori seme
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){     //sta inserendo un controllo di essere nel file giusto credo, tramite la parola RANDOMSEED che ci permette di riconoscerlo
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);                // uso la funzione setrandom per inizializzare tutti i parametri di cui ho bisogno avendoli caicati 
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   for(int i=0; i<20; i++){
      cout << rnd.Rannyu() << endl; // a questo punto ha gia creato la variabile rnd di tipo Random inizializzandola con valorri corretti ed è pronto a generare i 20 valori tramite il for
   }

   rnd.SaveSeed();
   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
