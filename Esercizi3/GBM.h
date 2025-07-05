#ifndef __GBM__
#define __GBM__

#include <string>
#include "random.h"

using namespace std;

// This class contains functions for generating random numbers using the RANNYU algorithm
class GBM {

private:
  double m_T;
  double m_S0, m_k, m_r, m_sigma;
  Random rnd;


protected:

public:
  // Default constructor
  GBM();
  //Constructor
  GBM(double S0, double r, double sigma, double k, double T);

  ~GBM();
  // Method to set the seed for the RNG
  
  double Price();

  double Price(int n_step);

};

#endif