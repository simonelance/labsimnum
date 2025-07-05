#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include <string>
#include <algorithm>  // std::shuffle
#include <random>     // std::mt19937, std::random_device
#include <map>
#include <iomanip>
#include "salesman.h"
#include <cstdlib>

using namespace std;

// conferisco posizioni casuali distribuite su circonferenza unitaria alle città
void Cromosoma::  Generate_circ(Random& _rnd){ 
    for(int i=0; i<_n_cities; i++){
        double theta=_rnd.Rannyu(0,2*M_PI);
        double x= cos(theta); double y= sin(theta);//genero coordinate su una circonferenza unitaria.

        _path[i]=  City(x, y, i+1) ;
    }

}

void Cromosoma::  Generate_squared(Random& _rnd){ 
    for(int i=0; i<_n_cities; i++){
        double x=_rnd.Rannyu();
        double y= _rnd.Rannyu();//genero coordinate su una circonferenza unitaria.

        _path[i]=  City(x, y, i+1) ;
    }

}


void Cromosoma:: Print_cities( ofstream &out){
    for (int i = 0; i < _n_cities; ++i) {
        out << _path[i].x << setw(10) << _path[i].y << setw(10) << _path[i].id << endl;
    }
}

void Cromosoma:: Shuffle(Random& _rnd){
    mt19937 gen(static_cast<unsigned>(_rnd.Rannyu() * 1e6));
    shuffle(_path.begin() +1 , _path.end(), gen); 
    this->Loss();

}

double Cromosoma:: Distance( City c1, City c2){
    return sqrt( pow( c1.x - c2.x, 2) + pow( c1.y -c2.y , 2 ));
}

void Cromosoma:: Loss(){
    double sum=0;
    for(int i=0; i<_n_cities; i++){
        if(i == _n_cities-1 ) sum += this->Distance(_path[i], _path[0]);
        else sum += this->Distance(_path[i], _path[i+1]);
    }
    _loss = sum;
}

Cromosoma& Cromosoma::operator=(const Cromosoma& other) {
    if (this != &other) {  // Evita auto-assegnazione
       // _n_cities = other._n_cities;
        _path = other._path;       // std::vector ha già operator=
        _loss = other._loss;
    }
    return *this;
}

Cromosoma::Cromosoma(const Cromosoma& other) {
    //_n_cities = other._n_cities;
    _loss = other._loss;
    _path = other._path;
}

void Cromosoma:: Swap(Random &rnd){

    int a= int(rnd.Rannyu(1,_n_cities)); // tra 1-34 perhe non voglio spostare la citta 1
    int b;
    do{b= int(rnd.Rannyu(1,_n_cities));
    }while(a == b);
    
    swap( *(_path.begin()+ a) , *(_path.begin()+ b) );

}

void Cromosoma:: ShiftBlock(Random &rnd){
    int m = int(rnd.Rannyu(1, _n_cities -1 )); // m vale al più 32 numero max di city shiftabili
    int start = int(rnd.Rannyu( 1, _n_cities -m ));


    int max_shift = _n_cities - ( m + start )+1;
    int n = int( rnd.Rannyu(1., max_shift ));

   

    vector <City> block(_path.begin() + start, _path.begin() + start + m); // 1. salva blocco
    _path.erase(_path.begin() + start, _path.begin() + start + m);             // 2. rimuovi blocco
    _path.insert(_path.begin() + start + n, block.begin(), block.end()); 

}

void Cromosoma:: ReverseBlock(Random &rnd){
    int m = int(rnd.Rannyu(1, _n_cities  )); // m vale al più 32 numero max di city shiftabili
    int start = int(rnd.Rannyu( 1, _n_cities -m ));

    vector <City> block(_path.begin() + start, _path.begin() + start + m); // 1. salva blocco
    reverse(block.begin(), block.end());

    _path.erase(_path.begin() + start, _path.begin() + start + m);             // 2. rimuovi blocco
    _path.insert(_path.begin() + start, block.begin(), block.end()); 

}

void Cromosoma:: SwapBlock(Random &rnd){

    int n_2= _n_cities/2;
    int m = int(rnd.Rannyu(1,  n_2 )); // m vale al più 32 in modo da identificare al piu la penultima city
    int start1 = int(rnd.Rannyu( 1, n_2 -m ));
    int start2 = int(rnd.Rannyu( start1, _n_cities -m ));

    swap_ranges(  _path.begin() + start1, _path.begin() + start1 +m , _path.begin() + start2);
    this->Check();
}

void Cromosoma:: Check(){ // controllo che non ci siano ripetizioni nel cromosoma.
    map<int, bool> checkmap;
    for(int i=1; i<= _n_cities; i++) checkmap[i]=false;

    for( int i=0; i<_n_cities; i++){
        int id = _path[i].id;
        auto it = checkmap.find(id);

        if (it == checkmap.end()) {
            cout << "Errore: città " << id << " non prevista nella mappa.\n";
            exit(-1);
        }
        if(it->second) {
            cout << "Errore: la città "<< _path[i].id<<" è visitata + di 1 volta."<< endl;
            exit(-1);
        }
        else it->second = true;
    }
}





/****************************************************************************************** */
/**************************************IMPLEMENTAZIONE POPULATION****************************/
/****************************************************************************************** */


void Population:: Generate_Population(Random _rnd){
    Cromosoma appo = _cromo; // in questo modo non viene modificato il cromosoma che uso per generare la popolazione. in un certo senso posso andare a veder equal era il mio cromosoma di partenza
    for( int i =0; i<_npop ; i++){
        if(i==0) _pop[i] = appo;
        else {
             appo.Shuffle(_rnd);
             _pop[i] = appo;} //shuffle aggiorna in automatico la loss del nuovo vettore
//sto facendo questo: mi sono creato un vettore di elementi Cromosoma, ciascuno di
//questi contiene un suo vettore path di città e una sua loss.
    }
}


void Population::SortByLoss() { // ordine crescente come vogliamo noi
    for(int i=0; i<_npop; i++) _pop[i].Loss();
    sort(_pop.begin(), _pop.end(),
        [](const Cromosoma &a, const Cromosoma &b) {//dico lla funzione sort con quale
            return a.get_Loss() < b.get_Loss();//criterio confrontare vari elementi Cromosoma
        } // la lambda returna true o false a seconda se la condizione è rispettata o meno
    );
}

void Population:: Print_cities_pop( int punto,const string flag, int k){
    ofstream out;
    
    if(punto ==1){ out.open("OUTPUT/circonferenza/path_"+ flag + ".out");
    }else if(punto ==2){ out.open("OUTPUT/prove/path_"+ flag + ".out");}
    else{ 
        cout << "Errore: punto identificativo esercizio sconosciuto. Esco"<< endl;
        exit(-1);}
    out << "X" << setw(10) << "Y"<< setw(10) << "city_id\n";


    _pop[k].Print_cities(out);//pop[k] è una variab romosoma => posso usare print
    out.close();
}

void Population:: Crossover(Random &rnd , ofstream &out){
    this ->SortByLoss();
    vector <Cromosoma> pop_new;
    for(int k=0; k< (_npop/2); k++){
        int a= int(  pow(rnd.Rannyu(),2) * _npop  ); //dalla popolazione ordinata con loss crescente
        // in modo che vengano estratti maggiormente i primi valori rispetto agli ultimi fvorendo crossover tra parents migliori
        int b;
        do{b= int(  pow(rnd.Rannyu(),2) * _npop  );
        }while(a == b);

        int cut = int(rnd.Rannyu(1,_ncities));

        vector<City> parent1=_pop[a].get_path();


        vector<City> parent2=_pop[b].get_path();
        vector<City> block1;
        vector<City> block2;

        for(int i =1; i<_ncities; i++){
            for(int j=cut; j<_ncities; j++){
                if( parent2[i].id== parent1[j].id){
                    City appo = parent2[i];
                    block1.push_back(appo);
                }
                if( parent1[i].id== parent2[j].id){
                    City appo = parent1[i];
                    block2.push_back(appo);
                }
            }
        }

        parent1.erase(parent1.begin()+ cut , parent1.end());
        parent2.erase(parent2.begin()+ cut , parent2.end());

        parent1.insert(parent1.begin()+ cut , block1.begin(), block1.end() );
        parent2.insert(parent2.begin()+ cut , block2.begin(), block2.end() );

        Cromosoma c1(parent1); // loss calcolata automaticamente da questo costruttore.
        Cromosoma c2(parent2);

        double pm1 = rnd.Rannyu();        
        if(pm1 < 0.1) c1.Swap(rnd);       
        else if(pm1 < 0.2) c1.SwapBlock(rnd);  
        else if(pm1 < 0.3) c1.ShiftBlock(rnd);  

        double pm2 = rnd.Rannyu();
        if(pm2 < 0.1) c2.Swap(rnd);
        else if(pm2 < 0.2) c2.SwapBlock(rnd);
        else if(pm2 < 0.3) c2.ShiftBlock(rnd);  

        c1.Check(); c2.Check();

        pop_new.push_back(c1);    pop_new.push_back(c2); // salvo a due a due i figli su un nuovo voettore
    }

    _pop= pop_new; // salvo i figli nella variabile privata.


}

void Population:: Mutation(Random &rnd ){
    
    for(int i =0; i<5; i++){
        int k= rnd.Rannyu(0,_npop);
        double p = rnd.Rannyu();

        if(p<0.25) _pop[k].ShiftBlock(rnd);
        else if(p<0.5)  _pop[k].SwapBlock(rnd);
        else if(p<0.75) _pop[k].Swap(rnd);
        else _pop[k].ReverseBlock(rnd);
        _pop[k].Loss();
    }

}

Population& Population::operator=(const Population& other) {
    if (this != &other) {  // Evita auto-assegnazione
            _cromo = other._cromo;
            _pop = other._pop;       // std::vector ha già operator=
            _npop = other._npop;
    }
    return *this;
}

double Population:: Half_Ave_Loss(){
    int n_2 = (_npop/2 );
    double sum=0;
    this->SortByLoss();
    for(int i =0; i< n_2 ; i++){
        sum += _pop[i].get_Loss();
    }
    double mean_loss= double(sum/n_2);
    return mean_loss;
}

