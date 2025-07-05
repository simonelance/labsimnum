#include "mpi.h"
#include <iostream>


using namespace std;
int main(int argc, char* argv[])
{
int size, rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
int k= rank;
int broadcast_message;
if (rank == k)
{
broadcast_message =  1 + k ;
}
// Broadcasting the message from process 0 to all other processes
MPI_Bcast(&broadcast_message, 1, MPI_INT, 0, MPI_COMM_WORLD);
if(rank != k ){
    cout << "Sono il processore "<< rank << " e ho ricevuto questo intero: " << broadcast_message<< " dal root core."<<endl ;
}
if(rank ==2)         cout << "Sono il processore "<< rank << " e ho ricevuto questo intero: " << 543 << " dal root core."<<endl ;

cout<<" Sono il nodo "<<rank<<" dei "<<size<<" che hai utilizzato!"<<endl;
MPI_Finalize();
return 0;
}