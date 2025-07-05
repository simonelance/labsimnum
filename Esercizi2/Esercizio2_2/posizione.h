#ifndef __Posizione__
#define __Posizione__

#include <string>
#include "random.h"

using namespace std;

// This class contains functions for generating random numbers using the RANNYU algorithm
class Posizione {

private:
  double x,y,z;

protected:

public:
  // Default constructor
  Posizione();
  //Costruttore con inizializzazione dei parametri di seme presoi dai files i cui nomi vengono comunicati nel main
  void UpdatePosDiscr(Random &);

  void UpdatePosCont(Random &);
  // Destructor
  ~Posizione();
  // Method to set the seed for the RNG
  void azzera();
  // Method to save the seed to a file

  double get_x(){
    return x;
  };

  double get_y(){
    return y;
  };

  double get_z(){
    return z;
  };
  
};

#endif 