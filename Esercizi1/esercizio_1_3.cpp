#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include <vector>

using namespace std;

double error(double AV, double AV2, int n) {
    if (n == 0) return 0;
    return sqrt((AV2 - AV * AV) / n);
}   //funzione per calcolare la deviazione standard.

double Eval(double L , double d, int dim, Random &rnd ) {
    
    int n_hit=0, n_tot=0;
    
    for(int i=0; i<dim; i++){
        double X1 = rnd.Rannyu(0,d); // suppongo le stanghette siano verticali sul piano, distanziate d lungo asse x

        double x_dir = rnd.Rannyu(-1,1);
        double y_dir = rnd.Rannyu(-1,1);
        double r = sqrt(x_dir*x_dir + y_dir*y_dir);

        double X2 = X1 + ( L* x_dir/r ); // voglio vedere dove cade la componente x del secondo punto, se cade oltre zero o oltre d allora ha colpito la stanghetta
        if (r < 1) {
            if( (X2 <=0) || (X2>=d) || (X1==0) ) n_hit ++;

            n_tot ++;
        }
    }
    double val= (2*L*n_tot) / (n_hit * d);

    return val;
}
 
int main (int argc, char *argv[]){
   //ESERCIZIO 1.3 ----------------------------------------------------------------------------------------

   if (argc != 5) {
        cout << endl << "ERROR! Program usage: {} <needle_length> <line_distance> <n_throws> <n_blocks>\n\n" <<  argv[0]<< endl;
        return -1;
    }

    // setting parameters
    double L = stod(argv[1]);                  // length of the needle
    double d = stod(argv[2]);                  // distance of the lines
    if (d <= L) {
        cout << endl <<"ERROR! <line_distance> must be greater than <needle_length>\n\n";
        return -1;
    }

    unsigned int nthrows = std::stod(argv[3]);       // number of throws
    unsigned int nblocks = std::stod(argv[4]);       // number of blocks

    string file_p =  "Primes";
    string file_s = "seed.in";
    Random rnd(file_s, file_p);
    ofstream out("data/risultati_1_3.out");
    out << "Block,Tot_throws,Progressive_val,Error\n";
    if(out.is_open()){
        cout << endl << "File risultati_1_3.out open correctly"<< endl;
    } else cerr << endl <<"Error opening output file"<< endl; 

    

    double sum1 = 0, sum2 = 0;
    double prog_val =0, prog_val2=0;
    double err=0;


    for (int i = 0; i < nblocks; ++i) { //itero sul numero dei blocchi
         // PROVA: errore nella definizione del calcolo di A_i^2

        double val= Eval(L,d , nthrows, rnd);
        double val2 = val*val ;
        sum1 += val ;
        sum2 += val2;

        

        prog_val = (double)sum1/(i+1);
        prog_val2 = (double)sum2/(i+1);
        err = error(prog_val, prog_val2, i);
        out << (i+1) << "," << (i+1)*nthrows << "," << prog_val << "," << err << std::endl;

    }

    cout << endl << "Miglior stima di= " << prog_val << " con errore= " << err << endl << endl  ;


}
    
    

    
    
   