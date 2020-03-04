CC = g++ -std=c++17
B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/jeu

$(B)/jeu: $(O)/Donjon.o
	$(CC) $(S)/jeu.cpp -o $(B)/jeu  $(O)/Donjon.o $(O)/Room.o $(O)/Door.o

$(O)/Donjon.o: $(O)/Room.o
	$(CC) $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Room.o: $(O)/Door.o
	$(CC) $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o:
	$(CC) $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean:
	rm -rf $(O)
	rm -rf $(B)
