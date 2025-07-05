# Compilatore e flag
CC = g++
CFLAGS = -Wall -O3 --std=c++20

# Target principale: costruisce tutto
all: esercizio_2_2.exe

# Eseguibile principale
esercizio_2_2.exe: esercizio_2_2.o random.o posizione.o
	$(CC) esercizio_2_2.o random.o posizione.o -o esercizio_2_2.exe $(CFLAGS)

# Target alias per semplicità
esercizio_2_2: esercizio_2_2.exe

# File oggetto
esercizio_2_2.o: esercizio_2_2.cpp random.h posizione.h
	$(CC) -c esercizio_2_2.cpp -o esercizio_2_2.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

posizione.o: posizione.cpp posizione.h
	$(CC) -c posizione.cpp -o posizione.o $(CFLAGS)

# Pulizia
clean:
	rm -f *.o *.exe seed.out
