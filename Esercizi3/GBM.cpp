#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "GBM.h"
#include "random.h"
#include <string>

using namespace std;

GBM :: GBM(){}
// Default constructor, does not perform any action

//Constructor
GBM :: GBM(double S0, double r, double sigma, double k, double T){
    m_k=k;
    m_r=r;
    m_sigma=sigma;
    m_S0=S0;
    m_T=T;
}


GBM :: ~GBM(){};

double GBM :: Price(){
    double S = m_S0 * exp( (m_r- (pow(m_sigma,2))/2)*m_T + m_sigma * rnd.Gauss(0,m_T));

    //double Call_profit= exp(-r*T) * max(0., S-k);
    return S;

}

double GBM :: Price(int n_step){
    double dt= m_T/n_step; // in base al numero di step inserito da tastiera, adeguo ila dimensione dell'intervallo di tempo dt
    
    double S= m_S0;
    

    for(int i=0; i<n_step; i++){
       S = S * exp( (m_r- (pow(m_sigma,2))/2 )*dt + m_sigma * rnd.Gauss(0,1) * sqrt(dt) );// aggiorno S in base al valore calcolato al tempo precedente
    
    }

    return S;

}