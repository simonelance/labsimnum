# Compilatore e flag
CC = g++
CFLAGS = -Wall -O3 --std=c++20

# Target di default: costruisce entrambi gli eseguibili
all: esercizio_2_1.exe 

esercizio_2_1.exe: esercizio_2_1.o random.o
	$(CC) esercizio_2_1.o random.o -o esercizio_2_1.exe


esercizio_2_1.o: esercizio_2_1.cpp random.h
	$(CC) -c esercizio_2_1.cpp -o esercizio_2_1.o $(CFLAGS)

# Compilazione di random.o da random.cpp
random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

# Pulizia dei file oggetto ed eseguibili
clean:
	rm -f *.o  esercizio_2_1 seed.out?