#ifndef __Salesman__
#define __Salesman__

#include <string>
#include <vector>
#include "random.h"

using namespace std;

struct City{
    double x, y;
    int id;

    // Costruttore di default
    City() : x(0), y(0), id(-1) {}

    City(double _x, double _y, int _id)
        : x(_x), y(_y), id(_id) {}
};


void Initialize(int &n_cities, int &npop, int &ngen, int &shape);


// This class contains functions for generating random numbers using the RANNYU algorithm
class Cromosoma {

private:
  int _n_cities =0 ;
  vector <City> _path;
  double _loss;

protected:

public:
  // Default constructor
  Cromosoma(){
    _path.resize(_n_cities);
  };

  Cromosoma(int ncit){
    _n_cities= ncit;
    _path.resize(_n_cities);
  };

  Cromosoma(vector<City> path, int ncit){
    _n_cities = ncit;
    _path.resize(_n_cities);
    _path=path;
    this->Loss();
    
  };
  // Destructor
  ~Cromosoma(){};

//copyconstructor
  Cromosoma(const Cromosoma& other);


  // Method to set the seed for the RNG
  void Generate_circ(Random&);

  void Generate_squared(Random&);

  void Shuffle(Random&);

  void Loss(); // ogni cromosoma calcola la loss del suo personale path

  double Distance( City c1, City c2);

  void Print_cities( ofstream &);

  void Reorder( vector<int>);

  
  int get_ncities(){
    return _n_cities;
  };

  double get_Loss () const {
    return _loss;
  }

  void Check();

  vector<City> get_path(){
    return _path;
  };
  
  vector<int> get_path_id();

  void set_path(vector<City> path){
    _path = path;
  };

  Cromosoma& operator=(const Cromosoma& other);

//SEZIONE MUTASSIONI
  void Swap(Random&);

  void ShiftBlock(Random &);

  void SwapBlock(Random &);

  void ReverseBlock(Random &);







  
};

class Population{

  private:
  Cromosoma _cromo; //tengo il cromosoma iniziale generato per poi farne lo shuffle
  // ed originare da lui la popolazione
  vector <Cromosoma> _pop;
  int _npop;
  int _ncities;

  public:

 // Costruttore di un oggetto di tipo population: 
 // ha bisogno del cromosoma capostipite da cui poi generare una popolazione, e del numero cromosoi da creare
  Population(Cromosoma cromo, int npop){
    
    _npop=npop;

    _ncities= cromo.get_ncities();
    _cromo = cromo; 
    _pop.resize(_npop);

  };

  void Generate_Population(Random);

  void SortByLoss() ;

  double get_Best(){
    this->SortByLoss();
    return _pop[0].get_Loss(); //ho ordinato la popolazione in ordine crescente
  }

  vector<City> get_path(int i){
    return _pop[i].get_path(); //pop[i] è una variabile di tipo cromosoma. l'_path mi resituisce il vettore di città
  };

  void Print_cities_pop( ofstream &,int );

  void Crossover(Random &rnd, ofstream &);

  Population& operator=(const Population& other);

  void Mutation(Random &rnd );

  double getWorstLoss();

  void Reorder( int , vector<int> );

  vector<int> get_path_pop(int );

  double Half_Ave_Loss();








};


/*struct Cromosoma {
    vector<City> path;
    double loss;
    int _ncities;

    // Costruttore utile
    Cromosoma(const vector<City>& p, double l, int n) : path(p), loss(l), _ncities(n) {}

    // Costruttore di default
    Cromosoma() : loss(0.0) {}
};*/



#endif 