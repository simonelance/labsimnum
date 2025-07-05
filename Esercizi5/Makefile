CC = g++
CFLAGS = -Wall -O3 -std=c++17
LDFLAGS = -larmadillo -llapack -lblas

# Target principale: costruisce tutto
all: esercizio_5_1.exe

# Eseguibile principale
esercizio_5_1.exe: esercizio_5_1.o random.o metropolis.o
	$(CC) esercizio_5_1.o random.o metropolis.o -o esercizio_5_1.exe $(LDFLAGS)

# Target alias per semplicità
esercizio_5_1: esercizio_5_1.exe

# File oggetto
esercizio_5_1.o: esercizio_5_1.cpp random.h metropolis.h
	$(CC) -c esercizio_5_1.cpp -o esercizio_5_1.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

metropolis.o: metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)

# Pulizia
clean:
	rm -f *.o *.exe seed.out