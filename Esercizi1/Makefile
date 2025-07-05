# Compilatore e flag
CC = g++
CFLAGS = -Wall -O3 --std=c++20

# Target di default: costruisce entrambi gli eseguibili
all: main.exe esercizio_1_1.exe esercizio_1_2.exe esercizio_1_3.exe

# Creazione dell'eseguibile main.exe
main.exe: main.o random.o
	$(CC) main.o random.o -o main.exe

# Creazione dell'eseguibile esercizio_1_1
esercizio_1_1.exe: esercizio_1_1.o random.o
	$(CC) esercizio_1_1.o random.o -o esercizio_1_1.exe

esercizio_1_2.exe: esercizio_1_2.o random.o
	$(CC) esercizio_1_2.o random.o -o esercizio_1_2.exe

esercizio_1_3.exe: esercizio_1_3.o random.o
	$(CC) esercizio_1_3.o random.o -o esercizio_1_3.exe

# Compilazione di main.o da main.cpp
main.o: main.cpp random.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)

# Compilazione di esercizio_1_1.o da esercizio_1_1.cpp
esercizio_1_1.o: esercizio_1_1.cpp random.h
	$(CC) -c esercizio_1_1.cpp -o esercizio_1_1.o $(CFLAGS)

esercizio_1_2.o: esercizio_1_2.cpp random.h
	$(CC) -c esercizio_1_2.cpp -o esercizio_1_2.o $(CFLAGS)

esercizio_1_3.o: esercizio_1_3.cpp random.h
	$(CC) -c esercizio_1_3.cpp -o esercizio_1_3.o $(CFLAGS)

# Compilazione di random.o da random.cpp
random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

# Pulizia dei file oggetto ed eseguibili
clean:
	rm -f *.o main.exe esercizio_1_1 seed.out?