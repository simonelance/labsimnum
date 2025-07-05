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
#include <armadillo>


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

  if(argc != 2) cout << "2 parameters needed: \n (1) <file.exe> \n (2) <4.2> or <4.3>" << endl;
    

  if(string(argv[1]) == "4.2"){
    
    string path = "../OUTPUT/FILES_4.2/";

    int nconf = 1;
    System SYS;
    SYS.initialize(path);
    SYS.initialize_properties(path);
    SYS.block_reset(0,path);
    int nsteps=SYS.get_nsteps();

    // per il primo blocco:
    for(int j=0; j < nsteps; j++){SYS.measure();}
    SYS.averages(1, path);
    SYS.block_reset(1,path);
    
    for(int i=1; i < SYS.get_nbl(); i++){ //loop over blocks , faccio 
      
      for(int j=0; j < nsteps; j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
        if(j%50 == 0){
//          SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
          nconf++;
        }
      }

      SYS.averages(i+1, path);
      SYS.block_reset(i+1,path);
      Progress_Bar(i,SYS.get_nbl());
    }
    SYS.finalize(path); // comando che tra le altre cose scrive le configurazioni finali.


  }else if(string(argv[1]) == "4.3"){
    // Mi serve calcolo di TEMPERATURE E POTENTIAL ENERGY per monitorare l'andamento del sistema una volta che il tempo sia stato invertito.

    string path = "../OUTPUT/FILES_4.3/";
    int nconf = 1;
    System SYS;
    SYS.initialize(path);
    SYS.initialize_properties(path);
    SYS.block_reset(0, path);
    int nsteps=SYS.get_nsteps();

        // per il primo blocco:
    SYS.measure();
    SYS.averages(1, path);
    SYS.block_reset(1,path);


    for(int i=1; i < SYS.get_nbl(); i++){ //loop over blocks , faccio 

      for(int j=0; j < nsteps; j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
        if(j%50 == 0){
//          SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
          nconf++;
        }
      }

      SYS.averages(i+1,path);
      SYS.block_reset(i+1, path);
      Progress_Bar(i,SYS.get_nbl());
    }
    SYS.finalize(path); // comando che tra le altre cose scrive le configurazioni finali.
    
    cout << endl << " -- Evolving the System backwards -- " << endl;
    SYS.reverse_time(path);
    //SYS.block_reset(0,path);

    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks , faccio 

      for(int j=0; j < nsteps; j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
        if(j%50 == 0){
//          SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
          nconf++;
        }
      }

      SYS.averages(i+1,path);
      SYS.block_reset(i+1, path);
      Progress_Bar(i,SYS.get_nbl());
    }
    SYS.finalize(path); // comando che tra le altre cose scrive le configurazioni finali.

  }else{
    cout << endl << "Unknown input parameter: \n 2 parameters needed: \n (1) <file.exe> \n (2) <4.2> or <4.3>";
  }

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
