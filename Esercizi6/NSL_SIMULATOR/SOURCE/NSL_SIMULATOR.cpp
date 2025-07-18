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
#include <iomanip>      // per std::setw
#include <string>
#include "system.h"

using namespace std;

void print_progress(int current, int total) {
  int bar_width = 50;
  float progress = float(current) / total;

  cout << "[";
  int pos = bar_width * progress;
  for (int i = 0; i < bar_width; ++i) {
      if (i < pos) cout << "=";
      else if (i == pos) cout << ">";
      else cout << " ";
  }
  cout << "] " << int(progress * 100.0) << " %\r"; // \r ritorna a inizio riga
  cout.flush();
}


int main (int argc, char *argv[]) {
  int nconf = 1;
  double temp =0.4;
  System SYS;
  string path= "../OUTPUT/FINAL_GIBBS/";

  SYS.initialize();
  SYS.initialize_properties(path);

  int total_steps = 21;
  
  for(int k = 0; k < total_steps; k++){
      temp += 0.1;
      string flag = to_string(temp);
      print_progress( k+1, total_steps ); // Stampa barra aggiornata

      
      SYS.Update_temp(temp);
      

      for(int i = 0; i < SYS.get_nbl(); i++){ // loop over blocks

          for(int j = 0; j < SYS.get_nsteps(); j++){ // loop over steps in a block
              SYS.step();
              SYS.measure();
//              if(j%50 == 0){
                 // SYS.write_XYZ(nconf); // Write configuration in XYZ format
                  //nconf++;
//              }
          }
          SYS.averages(i + 1, flag, path); // per dare il num di blocco corretto devo fare i+1
          SYS.block_reset(i + 1);
      }
    SYS.finalize();
    SYS.Set_restart(1);
    SYS.temp_reset(temp);
  }

  

  cout << endl << "Simulazione completata!" << endl;
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
