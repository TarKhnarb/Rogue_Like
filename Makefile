B = bin/
O = obj/
S = src/
FLAGS = -c -Wall
oO = -o $(O)

all: $(B)jeu

$(B)jeu: $(O)Donjon.o $(O)Room.o
	g++ -o $(B)jeu $(O)Donjon.o $(O)Room.o

$(O)Donjon.o: $(S)Donjon.cpp $(S)Donjon.h
	g++ $(FLAGS) $(S)Donjon.cpp $(oO)Donjon.o
	
$(O)Room.o: $(S)Room.cpp $(S)Room.h
	g++ $(FLAGS) $(S)Room.cpp $(oO)Room.o

$(O)Door.o: $(S)Door.cpp $(S)Door.h
    g++ $(FLAGS) $(S)Door.cpp $(oO)Door.o
	
clean:
	rm -rf $(O)*
	rm -rf $(B)*
