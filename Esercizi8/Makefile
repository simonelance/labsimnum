CC = g++
CFLAGS = -Wall -O3 -std=c++17
LDFLAGS = -larmadillo -llapack -lblas

# Target principale: costruisce tutto
all: main.exe main8_2.exe

# Eseguibile principale
main.exe: main.o random.o metropolis.o libreria.o
	$(CC) main.o random.o metropolis.o libreria.o -o main.exe $(LDFLAGS)

main8_2.exe: main8_2.o random.o metropolis.o libreria.o
	$(CC) main8_2.o random.o metropolis.o libreria.o -o main8_2.exe $(LDFLAGS)


# File oggetto
main.o: main.cpp random.h metropolis.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

metropolis.o: metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)

libreria.o: libreria.cpp libreria.h
	$(CC) -c libreria.cpp -o libreria.o $(CFLAGS)


# Pulizia
clean:
	rm -f *.o *.exe seed.out

# Target alias per semplicità
#main: main.exe
