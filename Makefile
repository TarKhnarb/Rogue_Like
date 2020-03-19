B = bin
O = obj
S = src
SQL = src/sqlite-amalgamation-3310100
FLAGS = -c -Wall

all: $(O) $(B) $(B)/Aspen

$(B)/Aspen: $(S)/Aspen.cpp $(O)/Donjon.o $(O)/Inventory.o $(O)/Position.o $(O)/Random.o $(O)/Npc.o $(O)/Entity.o
	g++ -ggdb $(S)/Aspen.cpp -o $(B)/Aspen $(O)/Donjon.o $(O)/Stage.o $(O)/Room.o $(O)/Door.o $(O)/Inventory.o $(O)/Objects.o $(O)/Position.o $(O)/Random.o $(O)/Npc.o $(O)/Entity.o

$(O)/Donjon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(O)/Door.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o:
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O)/Inventory.o: $(O)/Objects.o
	g++ $(FLAGS) $(S)/Inventory.cpp -o $(O)/Inventory.o

$(O)/Objects.o:
	g++ $(FLAGS) $(S)/Objects.cpp -o $(O)/Objects.o $(O)/sqlite3.o

$(O)/sqlite3.o:
	gcc $(FLAGS) $(SQL)/sqlite3.c $(SQL)/shell.c -o $(O)/sqlite3.o

$(O)/Position.o: $(O)/Random.o
	g++ $(FLAGS) $(S)/Position.cpp -o $(O)/Position.o

$(O)/Random.o:
	g++ $(FLAGS) $(S)/Random.cpp -o $(O)/Random.o

$(O)/Npc.o: $(O)/Entity.o
	g++ $(FLAGS) $(S)/Npc.cpp -o $(O)/Npc.o

$(O)/Entity.o: $(O)/Inventory.o
	g++ $(FLAGS) $(S)/Entity.cpp -o $(O)/Entity.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
