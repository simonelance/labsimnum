#include <iostream>
#include <string>
#include <cmath>
#include <armadillo>
#include <vector>



double Error(double AV, double AV2, int n);

double H_eval(double x, double sigma, double mu);

double Boltzmann(double beta, double Hnew, double Hold);
