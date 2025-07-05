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
#include "system.h"

using namespace std;

void Progress_Bar(int progress, int total, int bar_width=50) {

    float percentage = static_cast<float>(progress) / total;
    int pos = static_cast<int>(bar_width * percentage);

    std::string bar;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) bar += "=";
        else if(i==pos) bar += ">";
        else bar += " ";
    }

    std::cout<< "|" << bar << "| " << setprecision(3) << int(percentage * 100.0)<< "%\r";
    std::fflush(stdout);
}

int main (int argc, char *argv[]){

  int nconf = 1;
  System SYS;
  SYS.initialize();
  SYS.initialize_properties();
  SYS.block_reset(0);

  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
      SYS.step();

      SYS.measure(); // sto aggiornando ad ogni passo un vettore della classe system che contiene la misura media della mia grandezza per ciascun passo "_measurement"
      // la variabile _block_av invece contiene 'accumulo di _measurement ad ogni passo.

      if(j%50 == 0){
        
//        SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
        nconf++; // nconf calcola il numero di configurazioni totali senza riazzerarsi ad ogni nuovo blocco
      }
    }    
    //ho finito un blocco,
    SYS.averages(i+1); // scrive su file i valori che ci interessano (di pressione /en.cin/en.pot ..) applicando già il datablocking: ingfatti gli diamo in input il numero di blocco a cui siamo arrivati
    // e a funzione va a pescare variabili private nella classe su cui aveva precedentemente salvato i valori delle varie grandezze di interesse in modo da poterci agire.
    SYS.block_reset(i+1);

    //Progressbar
    Progress_Bar(i,SYS.get_nbl());
  }
  SYS.finalize();

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
