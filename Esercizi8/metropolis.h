#ifndef __Metropolis__
#define __Metropolis__

#include <string>
#include <armadillo>
#include "random.h"
#include "libreria.h"
#include <fstream>
#include <iomanip>

using namespace std;
using namespace arma;


// This class contains functions for generating random numbers using the RANNYU algorithm
class Metropolis {

private:
  double _step= 1;
  int _distr_type=0;
  Random _rnd;
  double _x = 0.;
  double _xold = 0.;
  double _a0=1.;
 //vec _x{100, 100, 100};
 //vec _xold{100, 100, 100};
  double _mu= 1.;
  double _sigma = 1.;
  int n_accept = 0;
  vec _H_ave ;
  vec _H_ave2;
  vec _err  ;
  int _n_blocks;

protected:

public:

  Metropolis(){;};

  ~Metropolis(){;};

  void OpenOutput(ofstream &, ofstream &);
  void OpenOutput(ofstream &, ofstream &, ofstream &); // vado a fare overload di questa funzione nel caso io debba aprire 3 files

  void Update();

  void SetParam(double sigma, double mu);


  bool Accept();

  double SearchStep(double,int,double, double);

  void SetType(int type){_distr_type =type;}

  double Campionamento();

  void Integral_BA(int , int );


  double Orbitales( vec );
  double Orbitalep( vec );
  
  double ProbabilityDistr(double );

  int Get_naccept(){
    return n_accept;
  };
  
  vec get_H_ave(){
    
    return _H_ave;
  };
  
  vec get_H_err(){
  return _err;
  };

  


  
};



#endif // __Random__