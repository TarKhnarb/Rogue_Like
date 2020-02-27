B = bin/
O = obj/
S = src/
FLAGS = -c -Wall

all: $(B)jeu

$(B)jeu: $(O)Donjon.o $(O)Salle.o
	g++ -o $(B)jeu $(O)Donjon.o $(O)Salle.o

$(O)Donjon.o: $(S)Donjon.cpp $(S)Donjon.h
	g++ $(FLAGS) $(S)Donjon.cpp -o $(O)Donjon.o
	
$(O)Salle.o: $(S)Salle.cpp $(S)Salle.h
	g++ $(FLAGS) $(S)Salle.cpp -o $(O)Salle.o
	
clean:
	rm -rf $(O)*
	rm -rf $(B)*
