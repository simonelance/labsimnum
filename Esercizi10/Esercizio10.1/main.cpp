#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <armadillo>
#include <iomanip>
#include "salesman.h"
#include <vector>
#include <string>
#include "mpi.h"

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


int main(int argc, char* argv[]){

    //ATTENZIONE, I PARAMETRI PER LA RISOLUZIONE DEL PROBLEMA VANNO IMPOSTATI DAL FILE INPUT.dat

    
    int npop;
    int Ngen;
    int N_cit;
    int shape; // deciderere con quale configurazione iniziale generare le città in modo random.
    Random rnd_i; // con la i di iniziale. la variabile rnd poi sarà usata successivamente e definita in modo diverso per ciascun processo parallelo.
    ofstream out;
    ofstream pout, loss_record;

    
    
    //secondo me da qua si puo inziare a parallelizzare il codice: il capostipite è stato creato, da quello iniziamo a produrre generazioni diverse con rnd variables diverse.
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Initialize(N_cit, npop, Ngen, shape);
    if(rank==0){
        cout << endl<<   "**************** PARAMETRI DI INPUT **************** " << endl ;
                           
        cout << endl <<  "Numero di città da visitare inizializzato a: " << N_cit;
        cout << endl <<  "Numero di cromosomi in una popolazione inizializzato a: " << npop;
        cout << endl <<  "Numero di generazioni inizializzato a: " << Ngen;
        if(shape ==0 ){cout << endl <<  "Le città saranno disposte randomicamente lungo una circonferenza." << endl ;
        }else if(shape ==1 ){cout << endl <<  "Le città saranno disposte all'interno di un quadrato." << endl ;
        }else if(shape ==2 ){cout << endl <<  "Le città sono i capoluoghi di provincia Italiani. " << endl;
        }
        cout << endl <<  "****************************************************"<< endl << endl ;
    }

    Cromosoma cromo(N_cit);
   

    if(shape ==0){ 
        cromo.Generate_circ(rnd_i); // cambiando il cromosoma capostipite della prima popolazione dovrebbe cambiare tutto
        out.open("OUTPUT/circonferenza/cities1.out");
        pout.open("OUTPUT/circonferenza/best_path_rank" + to_string(rank) + ".out");
        loss_record.open("OUTPUT/circonferenza/loss_record_"+ to_string(rank) + ".out");

    }else if(shape ==1){ 
        cromo.Generate_squared(rnd_i);
        out.open("OUTPUT/quadrato/cities1.out");
        pout.open("OUTPUT/quadrato/best_path_rank" + to_string(rank) + ".out");
        loss_record.open("OUTPUT/quadrato/loss_record_"+ to_string(rank) + ".out");

    }
    loss_record << "N" << "  "<< "Half_pop_ave" << setw(10) << "L\n";
    out << "X" << setw(10) << "Y"<< setw(10) << "city_id\n";
    pout << "X" << setw(10) << "Y"<< setw(10) << "city_id\n";
    
    cromo.Print_cities(out);
    cromo.Loss();
    
    if(rank ==0) cout<< " La lunghezza del percorso del primo cromosoma _Capostipite_ : "<< cromo.get_Loss() << endl << endl ;

    cout<< "-> Processo " << rank << " partito correttamente"<< endl;

    Random rnd(rank); // definisco un nuovo generatore di numeri random che prende valori diversi dal file Primes a seconda del processo.
    Population pop( cromo, npop);

    pop.Generate_Population(rnd);
    loss_record << 0 <<" " << pop.Half_Ave_Loss() << " " << pop.get_Best() << endl; // in questo modo mi scrivo proprio i valori di partenza della prima popo

    pop.Print_cities_pop(out, 0);
    for(int i=1; i<Ngen; i++){
        double p= rnd.Rannyu();
        
        
        if( p < 0.7 )  {    pop.Crossover(rnd, out);
        }else{              pop.Mutation( rnd);         }

        if(i%20 ==0){ // ogni 20 iterazioni scambia
            pop.SortByLoss(); // ordino la popolazione

            vector <int> ordine = pop.get_path_pop(0); //prendo vettore di interi con gli id del cromosoma migliore
            int Nc = ordine.size(); //numero citta nel path
            

            vector<int> tutti_ordini(Nc * size);

            
            MPI_Allgather(ordine.data(), Nc , MPI_INT,
              tutti_ordini.data(), Nc  , MPI_INT, // metto ancora Nc perche voglio il numero di dati raccolti perogni processo
              MPI_COMM_WORLD);


            for(int k=0; k<size; k++){
                vector <int> best(Nc);

                if(rank != k){
                    int start= k*Nc;
                    int end = (k+1) * Nc;
                    best.assign(tutti_ordini.begin() + start, tutti_ordini.begin() + end); // iteratore finale escluso dall'assegnazione.
                    pop.Reorder( npop-1, best );
                    pop.SortByLoss();
                     
                }
                
            }
        }
        loss_record << 0 <<" " << pop.Half_Ave_Loss() << " " << pop.get_Best() << endl; 

        //if(rank==0) printProgressBar(i+1, Ngen);

    }

    pop.SortByLoss();
    pop.Print_cities_pop(pout, 0); // stampo cromosoma 0 perchè li ho ordinati in ordine crescente di loss

    cout << endl << "Nella ultima generazione del processo _rank-"<< rank << "_, il percorso più breve misura: "<< pop.get_Best() << endl;
    
    out.close();
    loss_record.close();
    pout.close();



    MPI_Finalize();


    return 0;
}

