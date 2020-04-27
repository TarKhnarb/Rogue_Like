B = bin
O = obj
S = src
FLAGS = -c -Wall

all: $(O) $(B) $(B)/Aspen

$(B)/Aspen: $(O)/Party.o $(O)/Base.o $(O)/Npc.o
	g++ -ggdb $(S)/Aspen.cpp -o $(B)/Aspen $(O)/*.o -lsfml-graphics -lsfml-window -lsfml-system

$(O)/Party.o: $(O)/Donjon.o $(O)/Entity.o $(O)/Collider.o $(O)/AnimatedSprite.o $(O)/Projectile.o
	g++ $(FLAGS) $(S)/Party.cpp -o $(O)/Party.o

$(O)/Collider.o:
	g++ $(FLAGS) $(S)/Collider.cpp -o $(O)/Collider.o

$(O)/AnimatedSprite.o: $(O)/Animation.o
	g++ $(FLAGS) $(S)/AnimatedSprite.cpp -o $(O)/AnimatedSprite.o

$(O)/Animation.o:
	g++ $(FLAGS) $(S)/Animation.cpp -o $(O)/Animation.o

$(O)/Donjon.o: $(O)/Stage.o
	g++ $(FLAGS) $(S)/Donjon.cpp -o $(O)/Donjon.o

$(O)/Stage.o: $(O)/Room.o
	g++ $(FLAGS) $(S)/Stage.cpp -o $(O)/Stage.o

$(O)/Room.o: $(O)/Door.o $(O)/Entity.o $(O)/Chest.o
	g++ $(FLAGS) $(S)/Room.cpp -o $(O)/Room.o

$(O)/Door.o:
	g++ $(FLAGS) $(S)/Door.cpp -o $(O)/Door.o

$(O)/Base.o: $(O)/Chest.o $(O)/Entity.o
	g++ $(FLAGS) $(S)/Base.cpp -o $(O)/Base.o

$(O)/Chest.o: $(O)/Inventory.o $(O)/Entity.o
	g++ $(FLAGS) $(S)/Chest.cpp -o $(O)/Chest.o

$(O)/Projectile.o:
	g++ $(FLAGS) $(S)/Projectile.cpp -o $(O)/Projectile.o

$(O)/Entity.o: $(O)/Inventory.o
	g++ $(FLAGS) $(S)/Entity.cpp -o $(O)/Entity.o

$(O)/Inventory.o: $(O)/Object.o
	g++ $(FLAGS) $(S)/Inventory.cpp -o $(O)/Inventory.o

$(O)/Object.o:
	g++ $(FLAGS) $(S)/Object.cpp -o $(O)/Object.o

$(O)/Npc.o: $(O)/Entity.o $(O)/Upgrade.o
	g++ $(FLAGS) $(S)/Npc.cpp -o $(O)/Npc.o

$(O)/Upgrade.o:
	g++ $(FLAGS) $(S)/Upgrade.cpp -o $(O)/Upgrade.o

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)

clean: $(O) $(B)
	rm -rf $(O)
	rm -rf $(B)
