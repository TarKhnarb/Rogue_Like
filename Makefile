B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(B)/Aspen

$(B)/Aspen: $(S)/Aspen.cpp $(O)/Donjon.o $(O)/Inventory.o $(O)/Position.o $(O)/Random.o $(O)/Npc.o $(O)/Entity.o
	g++ -ggdb $(S)/Aspen.cpp -o $(B)Aspen $(O)/Donjon.o $(O)/Stage.o $(O)/Room.o $(O)/Door.o $(O)/Inventory.o $(O)/Objects.o $(O)/Position.o $(O)/Random.o $(O)/Npc.o $(O)/Entity.o

$(O)/Donjon.o: $(S)/Donjon.cpp $(S)/Donjon.h $(O)/Stage.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Stage.o: $(S)/Stage.cpp $(S)/Stage.h $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(S)/Room.cpp $(S)/Room.h $(O)/Door.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o: $(S)/Door.cpp $(S)/Door.h
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O)/Inventory.o: $(S)/Inventory.cpp $(S)/Inventory.h $(O)/Objects.o
	g++ $(FLAGS) $(S)/Inventory.cpp -o $(O)/Inventory.o

$(O)/Objects.o: $(S)/Objects.cpp $(S)/Objects.h
	g++ $(FLAGS) $(S)/Objects.cpp -o $(O)/Objects.o

$(O)/Position.o: $(S)/Position.cpp $(S)/Position.h $(O)/Random.o
	g++ $(FLAGS) $(S)/Position.cpp -o $(O)/Position.o

$(O)/Random.o: $(S)/Random.cpp $(S)/Random.h
	g++ $(FLAGS) $(S)/Random.cpp -o $(O)/Random.o

$(O)/Npc.o: $(S)/Npc.cpp $(S)/Npc.h $(O)/Entity.o
	g++ $(FLAGS) $(S)/Npc.cpp -o $(O)/Npc.o

$(O)//Entity.o: $(S)/Entity.cpp $(S)/Entity.h $(O)/Inventory.o
	g++ $(FLAGS) $(S)/Entity.cpp -o $(O)/Entity.o

clean:
	rm -rf $(O)/*
	rm -rf $(B)/*
