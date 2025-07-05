# Compilatore e flag
CC = g++
CFLAGS = -Wall -O3 --std=c++20

# Target principale: costruisce tutto
all: esercizio_3.exe

# Eseguibile principale
esercizio_3.exe: esercizio_3.o random.o GBM.o
	$(CC) esercizio_3.o random.o GBM.o -o esercizio_3.exe $(CFLAGS)

# Target alias per semplicità
esercizio_3: esercizio_3.exe

# File oggetto
esercizio_3.o: esercizio_3.cpp random.h GBM.h
	$(CC) -c esercizio_3.cpp -o esercizio_3.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

GBM.o.o: GBM.cpp GBM.h
	$(CC) -c GBM.cpp -o GBM.o $(CFLAGS)

# Pulizia
clean:
	rm -f *.o *.exe seed.out
