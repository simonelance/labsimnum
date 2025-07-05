#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <armadillo>
#include <iomanip>
#include "salesman.h"

#include <vector>

using namespace std;

void printProgressBar(int current, int total, int barWidth = 50) {
    float progress = float(current) / total;
    cout << "\r[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %" << flush;
}


int main(int argc, char* argv[]) {
    int punto = 0;

    if (argc < 2) {
        cout << "Errore: devi specificare un valore per 'punto' (1 oppure 2).\n";
        cout << "Esempio di utilizzo: ./programma 1\n";
        return 1;
    }

    punto = std::atoi(argv[1]);

    if (punto != 1 && punto != 2) {
        cout << "Errore: 'punto' deve essere 1 oppure 2.\n";
        return 1;
    }

    Cromosoma cromo;
    int npop=140;
    int N=1000; // per circonferenza bastano 600 steps, per quadrato 1000
    string flag;
    Random rnd;
    ofstream out; // questa variabile ofstream mi serve, inveec quando chiamo le variamili da un oggetto population creo tutto dentro al metodo.
    ofstream best_out;

    

    if(punto ==1 ){
        cromo.Generate_circ(rnd);
        cout << "Cromosoma capostipite con path lungo traiettoria circolare \n";
        out.open("OUTPUT/circonferenza/path_0.out");
        best_out.open("OUTPUT/circonferenza/best_distances.out");
    }else if(punto ==2 ){cromo.Generate_squared(rnd); // cambiando il cromosoma capostipite della prima popolazione dovrebbe cambiare tutto
        cout << "Cromosoma capostipite con path interna ad un quadrato \n";
        out.open("OUTPUT/quadrato/path_0.out");
        best_out.open("OUTPUT/quadrato/best_distances.out");
    }else{ 
        cout << "Errore: punto identificativo esercizio sconosciuto. Esco"<< endl;
        exit(-1);
    }
    out << "X" << setw(10) << "Y"<< setw(10) << "city_id\n";
    best_out << "N" << "  "<< "Half_pop_ave" << setw(10) << "L\n";

    cromo.Print_cities(out);
    cromo.Loss();
    cout<< " Ho stampato su file le città"<< endl ;
    cout<< " La lunghezza del percorso del primo cromosoma: "<< cromo.get_Loss() << endl ;



    Population pop( cromo, npop);
    pop.Generate_Population(rnd);

    for(int i=0; i<N; i++){
        double p= rnd.Rannyu();
        
        if( p < 0.7 )  {
            pop.Crossover(rnd, out);
        }else{  
            pop.Mutation( rnd);
        }
        if (i==200) {
            flag = "200";
            pop.Print_cities_pop(punto, flag, 0);
        }
        if (i==400){
            flag = "400";
            pop.Print_cities_pop(punto, flag, 0);
        } 

        printProgressBar(i, N);

        best_out << i+1  <<"   " << pop.Half_Ave_Loss() <<"   " << pop.get_Best() << endl ;

    }
    flag = to_string(N);
    pop.SortByLoss();
    pop.Print_cities_pop(punto, flag, 0);

    cout << endl << "Nella prima generazione, il percorso più breve misura: "<< pop.get_Best() << endl;
    
    out.close();






    return 0;
}

