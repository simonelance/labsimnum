#ifndef __Metropolis__
#define __Metropolis__

#include <string>
#include <armadillo>
#include "random.h"
#include <fstream>

using namespace std;
using namespace arma;


// This class contains functions for generating random numbers using the RANNYU algorithm
class Metropolis {

private:
  int _orbitale=0;
  double _step= 1.1;
  int _distr_type=0;
  Random _rnd;
  double _a0=1;
  vec _x{100, 100, 100};
  vec _xold{100, 100, 100};
  int n_accept = 0;

protected:

public:

  Metropolis(){;};

  Metropolis(int type, int orb){_distr_type =type; _orbitale =orb;}

  ~Metropolis(){;};

  void OpenOutput(ofstream &, ofstream &);

  void Initialize_pos( double x, double y, double z );


  void Update();

  bool Accept();

  double SearchStep(double,int,double, double);

  void SetType(int type){_distr_type =type;}

  vec Campionamento();

  double Orbitales( vec );
  double Orbitalep( vec );

  int Get_naccept(){
    return n_accept;
    };

  


  
};

#endif // __Random__