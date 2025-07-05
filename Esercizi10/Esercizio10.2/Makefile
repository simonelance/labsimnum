# Compilatore MPI C++
CC = mpicxx
# Flags di compilazione
CFLAGS = -Wall -O3 -std=c++17
# Flags di linking per librerie esterne. mpicxx gestirà il linking di MPI.
LDFLAGS = -larmadillo -llapack -lblas

# Nome dell'eseguibile parallelizzato
TARGET = main.exe

# Target principale: costruisce tutto
all: $(TARGET)

# Eseguibile principale
$(TARGET): main.o random.o salesman.o
	$(CC) $^ -o $@ $(LDFLAGS)

# File oggetto (le dipendenze rimangono le stesse)
main.o: main.cpp random.h salesman.h
	$(CC) -c $< -o $@ $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c $< -o $@ $(CFLAGS)

salesman.o: salesman.cpp salesman.h
	$(CC) -c $< -o $@ $(CFLAGS)

# Target per l'esecuzione parallelizzata
# Puoi specificare il numero di processi (es. -np 4) qui.
# Modifica '4' con il numero di processi desiderati.
run: $(TARGET)
	mpirun -np 4 ./$(TARGET)

# Pulizia
clean:
	rm -f *.o $(TARGET) seed.out

# Target alias per semplicità (se vuoi mantenere 'main' come alias per la compilazione)
#main: $(TARGET)