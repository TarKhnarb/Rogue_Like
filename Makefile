B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/Aspen

$(B)/Aspen: $(O)/Donjon.o
	g++ -ggdb $(S)/Aspen.cpp -o $(B)/jeu $(O)/Donjon.o $(O)/Stage.o $(O)/Room.o $(O)/Door.o

$(O)/Donjon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

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
