B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/Aspen

$(B)/Aspen: $(O)/menu.o
	g++ -ggdb $(S)/Aspen.cpp -o $(B)/Aspen $(O)/*.o

$(O)/Donjon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(O)/Door.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o:
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O)/Inventory.o: $(O)/Object.o
	g++ $(FLAGS) $(S)/Inventory.cpp -o $(O)/Inventory.o

$(O)/Object.o:
	g++ $(FLAGS) $(S)/Object.cpp -o $(O)/Object.o

$(O)/Random.o:
	g++ $(FLAGS) $(S)/Random.cpp -o $(O)/Random.o

$(O)/Upgrade.o:
	g++ $(FLAGS) $(S)/Upgrade.cpp -o $(O)/Upgrade.o

$(O)/Npc.o: $(O)/Entity.o $(O)/Upgrade.o
	g++ $(FLAGS) $(S)/Npc.cpp -o $(O)/Npc.o

$(O)/Entity.o: $(O)/Inventory.o $(S)/Position.h
	g++ $(FLAGS) $(S)/Entity.cpp -o $(O)/Entity.o

$(O)/Projectile.o: $(S)/Position.h
	g++ $(FLAGS) $(S)/Projectile.cpp -o $(O)/Projectile.o

$(O)/winTxt.o:
	g++ $(FLAGS) $(S)/winTxt.cpp -o $(O)/winTxt.o

$(O)/game.o: $(O)/Projectile.o $(O)/Donjon.o $(O)/Entity.o
	g++ $(FLAGS) $(S)/game.cpp -o $(O)/game.o

$(O)/menu.o: $(O)/game.o $(O)/Entity.o $(O)/winTxt.o
	g++ $(FLAGS) $(S)/menu.cpp -o $(O)/menu.o



$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
