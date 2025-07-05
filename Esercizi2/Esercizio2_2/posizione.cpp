#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include "posizione.h"
#include <string>

using namespace std;

Posizione :: Posizione(){
    x=0.;
    y=0.;
    z=0.;
    }

Posizione :: ~Posizione(){;}

void Posizione :: UpdatePosDiscr(Random &rnd){
    int comp = int(rnd.Rannyu(0.,3.));     // genero un numero che può valere 0,1,2 e ne faccio la parte intera
    double verso = rnd.Rannyu();    // una volta estratta in modo randomico la componente, vado a estrarre il verso in cui avverrà lo step: 1=avanti, 0=indietro.
   
    if( verso<0.5 ){
        if(comp==0 ) x+=1.;
        if(comp==1 ) y+=1.;
        if(comp==2 ) z+=1.;
    
    }else{
        if(comp==0 ) x+= (-1.);
        if(comp==1 ) y+= (-1.);
        if(comp==2 ) z+= (-1.);
    }
}

void Posizione :: UpdatePosCont(Random &rnd){
   
    double theta = rnd.GenTheta(); //theta è compreso tra 0-π ()
    double phi = rnd.GenPhi(); // phi compreso tra 0-2π (pi greco si genera con ctrl+shift premuto e poi u03c0)

    x += sin(theta)*cos(phi);
    y += sin(theta)*sin(phi);
    z += cos(theta); // non mi servono più la componente ed il verso: questi mi sono gia forniti dalle funzioni seno e coseno che possono ssumere valori positivi o negativi
                     // e sono proiettate sugli assi
    
}

void Posizione :: azzera(){
    x=0.;
    y=0.;
    z=0.;
    }