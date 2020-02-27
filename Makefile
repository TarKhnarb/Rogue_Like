B = bin/
O = obj/
S = src/
FLAGS = -c -Wall

all: $(B)jeu

$(B)jeu: $(O)Donjon.o $(O)Room.o
	g++ -o $(B)jeu $(O)Donjon.o $(O)Room.o

$(O)Donjon.o: $(S)Donjon.cpp $(S)Donjon.h
	g++ $(FLAGS) $(S)Donjon.cpp -o $(O)Donjon.o
	
$(O)Room.o: $(S)Room.cpp $(S)Room.h
	g++ $(FLAGS) $(S)Room.cpp -o $(O)Room.o

$(O)Door.o: $(S)Door.cpp $(S)Door.h
    g++ $(FLAGS) $(S)Door.cpp -o $(O)Door.o
	
clean:
	rm -rf $(O)*
	rm -rf $(B)*