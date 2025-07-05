#ifndef __Funzione__
#define __Funzione__

#include <string>
#include <armadillo>
#include "random.h"

using namespace std;
using namespace arma;


// This class contains functions for generating random numbers using the RANNYU algorithm
class Funzione {

private:
    Random rnd

protected:

public:

  double Orbitales(vec, double a0 ){
    double psi = ( pow(a0, (-3/2))/sqrt(M_PI) * exp( (-r)/a0));
    return (psi*psi);
  };

  double p1(double r);


  
};

#endif // __Random__