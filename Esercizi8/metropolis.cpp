#include "metropolis.h"
#include <cmath>


using namespace std;



double Metropolis :: Orbitales( vec x ){
    double r = norm(x,2);
    double psi = ( (pow(_a0, (-3/2)) / sqrt(M_PI)) * exp( (- r )/_a0));
    return (psi*psi);
}

double Metropolis :: Orbitalep( vec x ){
    double r = norm(x,2);
    double psi =  exp( (- r )/2*_a0) * x(2);
    return (psi*psi);
}



double Metropolis :: ProbabilityDistr(double x){
    double e1= exp(-pow(x-_mu,2)/pow(_sigma,2));
    double e2= exp(-pow(x+_mu,2)/pow(_sigma,2));
    double e3= exp((-x*x-_mu*_mu)/pow(_sigma,2));

    return e1 + e2+ 2*e3;
}

void Metropolis :: OpenOutput(ofstream & out_pos, ofstream & out_r){ // QUESTA FUNZIONE VIENE USATA ANCHE NELL'ES 8.2 ALL'INTERNO DI BLOCKING AVE
    
    out_pos.open("OUTPUT_8.1/campionamento_psi_final.out");
    out_r.open("OUTPUT_8.1/data_blocking_final.out");
    
    
    if(out_r.is_open() | out_pos.is_open()){
        //cout << endl << "Files aperti correttamente"<< endl;
    } else cerr << endl <<"Errore in apertura files"<< endl;
    
    out_pos << "posizione\n" ;
    out_r << "n_block" << setw(15) <<  "H_average" << setw(15) <<  "errore\n";
    
}

void Metropolis::OpenOutput( ofstream &out_pos, ofstream &out_r, ofstream &out8_2) {
    out_pos.open("OUTPUT_8.2/campionamento_psi.out");
    out_r.open("OUTPUT_8.2/data_blocking.out");
    out8_2.open("OUTPUT_8.2/simulated_annealing.out");

    if (out_pos.is_open() && out_r.is_open() && out8_2.is_open()) {
        std::cout << "\nTutti i file aperti correttamente\n";
    } else {
        std::cerr << "\nErrore nell'apertura di uno o più file\n";
    }

    out_pos << "posizione\n";
    out_r << "n_block" << setw(15) <<  "H_average" << setw(15) <<  "errore\n";
    out8_2 <<  "n_block" << setw(15) << "T" << setw(10) <<  "sigma" << setw(15) <<  "mu" << setw(15) <<  "<H>" << setw(15) <<  "H_err\n";
}

void Metropolis :: Update(){
     _x += _rnd.Rannyu(-1, 1) *_step ;
}

void Metropolis :: SetParam(double sigma, double mu){
    _sigma=sigma;
    _mu= mu;
}

bool Metropolis :: Accept(){

    double alpha=0.;
    alpha= fmin(1, (ProbabilityDistr(_x)/ProbabilityDistr(_xold)));

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
    cout << "Rapporto <naccept>/<ntot> = "<< ratio <<endl;
    return _step;
}

double Metropolis :: Campionamento(){

    this->Update(); // aggiorno le componenti del vettore posizione e provo a vedere se saranno accettate o rifiutate.

    double alpha = fmin(1, (ProbabilityDistr(_x)/ProbabilityDistr(_xold)));
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

void Metropolis :: Integral_BA(  int n_blocks, int n_steps){ //ottenere il valore dell'integrale tramite la blocking average.
    // void perchè salva i valori dell'integrale in variabili private che saranno accessibili tramite il metodo get.
    ofstream out;
    ofstream pos_out;
    this->OpenOutput(pos_out, out);
    _n_blocks=n_blocks;

    _H_ave = zeros<vec>(n_blocks);
    _H_ave2 = zeros<vec>(n_blocks);
    _err = zeros<vec>(n_blocks);

    for(int i=0; i<n_blocks;i++){
            double H_sum=0;
            for( int j=0; j< n_steps; j++){

                double x = this->Campionamento()  ;
                double H_temp = H_eval(x, _sigma, _mu );

                H_sum += H_temp; 
                if(i==(n_blocks-1)){
                    pos_out << x <<  " ";  
                    pos_out << "\n";}
            }
            if(i==0){
                _H_ave(i) = H_sum/n_steps; // nel nuovo elemento del vettore salvo la somma dei valori che mi interessano
                _H_ave2(i) = (_H_ave(i)*_H_ave(i));
                _err(i)= 0;
            }else{
                _H_ave(i) = (_H_ave(i-1) + H_sum/n_steps)  ;
                _H_ave2(i) = _H_ave2(i-1) + (H_sum/n_steps)*(H_sum/n_steps) ;
                _err(i)= Error( _H_ave(i)/(i+1), _H_ave2(i)/(i+1), i);
            }
            //cout << "   " << (r_ave2(i)/(i+1))-pow(r_ave(i)/(i+1),2);
            if(i==(n_blocks-1)){
                out << i + 1 << setw(15) << (_H_ave(i)/(i+1)) << setw(15) << _err(i) << "\n";
            }
        }
        for(int  i=0; i<_n_blocks;i++) _H_ave(i) /= (i+1); // che sono i valori stampati nel file.


    pos_out.close();
    out.close();
    
}