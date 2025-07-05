#include "metropolis.h"
#include <cmath>


using namespace std;



double Metropolis :: Orbitales( vec x ){
    double r = norm(x,2);
    double psi = ( (pow(_a0, (-3/2)) / sqrt(M_PI)) * exp( (- r )/_a0));
    return (psi*psi);
}

void Metropolis :: Initialize_pos( double x, double y, double z ){
   _x = {x, y, z};
   _xold = {x, y, z};
}

double Metropolis :: Orbitalep( vec x ){
    double r = norm(x,2);
    double psi =  exp( (- r )/2*_a0) * x(2);
    return (psi*psi);
}

void Metropolis :: OpenOutput(ofstream & out_pos, ofstream & out_r){
    string pos;
    string r ;
    if(_orbitale==0 && _distr_type ==0){
        pos = "data/orbs_posiz_unif_5_1.out";
        r = "data/orbs_ris_unif_5_1.out";
    }else if(_orbitale==0 && _distr_type ==1){
        pos = "data/orbs_posiz_gaus_5_1.out";
        r = "data/orbs_ris_gaus_5_1.out";
    }else if(_orbitale==1 && _distr_type ==1){
        pos = "data/orbp_posiz_gaus_5_1.out";
        r = "data/orbp_ris_gaus_5_1.out";
    }else if(_orbitale==1 && _distr_type ==0){
        pos = "data/orbp_posiz_unif_5_1.out";
        r = "data/orbp_ris_unif_5_1.out";
    }else cerr << endl <<"Errore: casistica ignota"<< endl;

        out_pos.open(pos);
        out_r.open(r);
    
    out_pos << "x y z\n" ;
    out_r << "n_block r_average errore\n";
    
}

void Metropolis :: Update(){
    if(_distr_type==0) {
        for(int i=0 ; i<3 ; i++) _x(i) += _rnd.Rannyu(-1, 1) *_step ;}
    else if( _distr_type==1){
        for(int i=0 ; i<3 ; i++) _x(i) += _rnd.Gauss(0,_step)  ;}
    else{cout << endl << "Errore, distribuzione di probabilità di partenza ignota.";
    }
}

bool Metropolis :: Accept(){

    double alpha=0.;
    if(_orbitale==0) alpha= fmin(1, (Orbitales(_x)/Orbitales(_xold)));
    else if(_orbitale==1) alpha= fmin(1, (Orbitalep(_x)/Orbitalep(_xold)));
    else{ cerr<< "Orbitale da campionare non riconosciuto."<< endl; exit(-3);}

    double r = _rnd.Rannyu() ;
    int ris =0;

    if( r <= alpha ){
        ris=1;
        _xold=_x; // se il valore è accettato salvo nell xold questo valore in modo da poter nuovamente aggiornare _x nel nuovo passo e paragonarlo alla sua versione precedente
    }
    else{
        _x= _xold;// altrimenti riazzero il passo e riprovo ad aggiornarlo con un altro numero casuale
    }
    return ris;
}

double Metropolis :: SearchStep( double prec, int N, double target, double step){
    double corr = step;
    int n_acc=0;
    double ratio=0.;
    do{
        _step = step;
        n_acc = 0;
       
        //_x(0)=  //= arma::zeros<arma::vec>(3); // re inizializzo i vettori
        //_xold = _x;

        for(int i =0; i<N; i++){
            this->Update();
            bool b= this->Accept();
            if(b) n_acc ++;
        }
        ratio = (double)n_acc/N;

        if(corr>prec) corr /=2.;
        else if (corr< prec) corr=prec;

        if(ratio< (target-prec)) step -= corr;
        else if (ratio >(target-prec)) step += corr;
    } while ((ratio < target - prec ) || (ratio > target + prec ));
    cout << "Trovato lo step ottimale per la simulazione <step> = "<< _step<<endl;
    return _step;
}

vec Metropolis :: Campionamento(){

   this->Update(); // aggiorno le componenti del vettore 
    //x1(3)+= sqrt(x1(0)*x1(0)+x1(1)*x1(1)+x1(2)*x1(2)); // cosi non va bene perche ad ogni iterazione il vettore viene re inizializzato e le misure di raggio accumulate cancellate


    double alpha =0.;
    if(_orbitale==0) alpha= fmin(1, (Orbitales(_x)/Orbitales(_xold)));
    else if(_orbitale==1) alpha= fmin(1, (Orbitalep(_x)/Orbitalep(_xold)));

    double r = _rnd.Rannyu() ;

    if( r <= alpha ){
        n_accept ++;
        _xold=_x; // se il valore è accettato salvo nell xold questo valore in modo da poter nuovamente aggiornare _x nel nuovo passo e paragonarlo alla sua versione precedente
    }
    else{
        _x= _xold;// altrimenti riazzero il passo e riprovo ad aggiornarlo con un altro numero casuale
    }

    return _x;
    
}