CC = g++ -std=c++17
B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/jeu

$(B)/jeu: $(S)/jeu.cpp $(O)/Donjon.o $(O)/Room.o $(O)/Door.o
	$(CC) $(S)/jeu.cpp -o $(B)/jeu  $(O)/Donjon.o $(O)/Room.o $(O)/Door.o

$(O)/Donjon.o: $(S)/Donjon.cpp $(S)/Donjon.h $(S)/Room.h $(S)/Door.h
	$(CC) $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Room.o: $(S)/Room.cpp $(S)/Room.h $(S)/Door.h
	$(CC) $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o: $(S)/Door.cpp $(S)/Door.h
	$(CC) $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean:
	rm -rf $(O)*
	rm -rf $(B)*
