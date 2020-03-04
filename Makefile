B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/jeu

$(B)/jeu: $(O)/Donjon.o
	g++ $(S)/jeu.cpp -o $(B)/jeu $(O)/Donjon.o $(O)/Room.o $(O)/Door.o

$(O)/Donjon.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Room.o: $(O)/Door.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o:
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)