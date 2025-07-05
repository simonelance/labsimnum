CC = g++
CFLAGS = -Wall -O3 -std=c++17
LDFLAGS = -larmadillo -llapack -lblas

# Target principale: costruisce tutto
all: main.exe 

# Eseguibile principale
main.exe: main.o random.o salesman.o 
	$(CC) main.o random.o salesman.o -o main.exe $(LDFLAGS)

# File oggetto
main.o: main.cpp random.h salesman.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

salesman.o: salesman.cpp salesman.h
	$(CC) -c salesman.cpp -o salesman.o $(CFLAGS)


# Pulizia
clean:
	rm -f *.o *.exe seed.out

# Target alias per semplicità
#main: main.exe
