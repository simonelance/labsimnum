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
#include <typeinfo>


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

  if(argc != 2 ){
    cerr << "2 parameters needed: file_name.exe and exercise_number;" << endl;
    cerr << "- <7.2> - <7.3> - <7.4> - " << endl; 
    //GUIDA ALL'UTILIZZO:  nel <7.2> dovro eseguire con 500000 blocchi da 1 step. poi lo studio dell'errore in fz del numero di passi è fatto con script python. 
    return 0;
  }
  std::string arg = argv[1];
  std::string path;

  if (arg == "7.2") path = "../OUTPUT/7.2/";
  else if (arg == "7.3") path = "../OUTPUT/7.3/";
  else if (arg == "7.4") path = "../OUTPUT/7.4/";
  else {
    cerr << "Unknown parameter!" << endl;
    return -1;
  }
      
  System SYS;
  SYS.initialize();  // ha dentro initialize_velocities che ha dentro il parametro restart
  SYS.initialize_properties(path);  
  SYS.block_reset(0) ; 
  SYS.Equilibrate(2000);


  for(int i = 0; i < SYS.get_nbl(); i++){ // loop over blocks
    print_progress(i + 1,SYS.get_nbl()); // Stampa barra aggiornata
    
      for(int j = 0; j < SYS.get_nsteps(); j++){ // loop over steps in a block
          SYS.step();
          SYS.measure();
//            if(j%50 == 0){
             // SYS.write_XYZ(nconf); // Write configuration in XYZ format
              //nconf++;
//            }
      }
      SYS.averages(i + 1,path);
      SYS.block_reset(i + 1);
  }
  SYS.finalize();
  int naccepted = SYS.get_naccepted();

  //cout << endl << "acceptance ratio: "<< naccepted/double(SYS.get_nbl()*SYS.get_npart());
  

  

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
