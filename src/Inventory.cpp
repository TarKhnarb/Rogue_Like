#include "Inventory.h"

Inventory::Inventory(unsigned idBasicStat, unsigned stuffSize, unsigned bagSize) // stuffSize = 0 ou 3
: basicStat {idBasicStat}
, stuff {stuffSize, nullptr}
, bag {bagSize, nullptr}
{ }

Inventory::~Inventory(){

	for(Object *p : stuff){
		delete p;
		p = nullptr;
	}

	for(Object *p : bag){
		delete p;
		p = nullptr;
	}
}

void Inventory::equip(unsigned bagIndex){

	assert(bagIndex < bag.size() && bag[bagIndex]);

	unsigned stuffIndex;
	switch(bag[bagIndex]->getType()){ // Cherche le type de l'object a equiper
		case Object::projectile:
			stuffIndex = 0;
			break;

		case Object::armor:
			stuffIndex = 1;
			break;

		case Object::amulet:
			stuffIndex = 2;
			break;

		default:
			throw std::runtime_error {"Inventory::equip(" + std::to_string(bagIndex) + ") - Unequipable object"}; // penser a fair ele catch
	}

	swapStuffBag(stuffIndex, bagIndex);
}

void Inventory::unequip(unsigned stuffIndex)
{
	assert(stuffIndex < stuff.size());

	auto found = std::find(bag.begin(), bag.end(), nullptr);
	if (found == bag.end())
		throw std::runtime_error {"Inventory::unequip(" + std::to_string(stuffIndex) + ") - Bag is full"};

	*found = stuff[stuffIndex];
	stuff[stuffIndex] = nullptr;
}

void Inventory::addObject(unsigned id, unsigned objectNb){

    while (objectNb > 0){
        auto pred = [id] (Object* obj) -> bool { return obj && obj->getId() == id && obj->getObjectNumber() < obj->getMaxStack(); }; // Si l'id est bien un object, que l'id correspond et que son maxStack n'est pas atteint
        auto found = std::find_if(bag.begin(), bag.end(), pred); // Recherche si pred entre le début et la fin du bag

        if (found != bag.end()){ // Si on trouve une case avec pred
            objectNb = (*found)->addObjectNumber(objectNb); // On ajoute a cet object existant le nombre d'object
        }
        else{ // Si on ne trouve pas
            found = std::find(bag.begin(), bag.end(), nullptr); // On cherche les cases vides
            if (found == bag.end()) // Si aucune case n'est vide
                throw std::runtime_error {"Inventory::addobject(" + std::to_string(id) + ") - Bag is full"}; // Erreur a afficher plus tard pour le joueur

            *found = new Object {id}; // On créer un nouvel object a la case trouvée
            objectNb -= 1; // On désincrémente car quand on créer un object, on l'init a 1 car sinon il ne peut exister (trivial quand on le sait)
            objectNb = (*found)->addObjectNumber(objectNb); // On ajoute a cet object existant le nombre d'object
        }
    }
}

unsigned Inventory::removeObject(unsigned bagIndex){

	assert(bagIndex < bag.size() && bag[bagIndex]);

	unsigned objectId = bag[bagIndex]->getId();
	delete bag[bagIndex];
	bag[bagIndex] = nullptr;

	return objectId;
}

unsigned Inventory::removeObject(unsigned id, unsigned objectNb)
{
	unsigned removedObjects = 0;

	for (auto p : bag)
	{
		if (p && p->getId() == id)
		{
			unsigned idObjectNb = p->getObjectNumber();

			if (objectNb >= idObjectNb)
			{
				delete p;
				p = nullptr;
				objectNb -= idObjectNb;
				removedObjects += idObjectNb;
			}
			else
			{
				p->setObjectNumber(idObjectNb - objectNb);
				objectNb = 0;
				removedObjects += objectNb;
			}
		}
	}

	return removedObjects;
}

unsigned Inventory::getNumber(unsigned id) const
{
    unsigned count = 0;

    for (auto p : bag)
    {
        if (p && p->getId() == id)
        {
            count += p->getObjectNumber();
        }
    }

    return count;
}

void Inventory::swapBagBag(unsigned bagIndex1, unsigned bagIndex2){

	assert(bagIndex1 < bag.size() && bagIndex2 < bag.size());

	Object *temp {bag[bagIndex1]};
	bag[bagIndex1] = bag[bagIndex2];
	bag[bagIndex2] = temp;
}

std::vector<int> Inventory::getAllStats() const{

	std::vector<int> stats = basicStat.getStats();

	for (Object* p : stuff)
	{
		if (p)
		{
			std::vector<int> stuffStats = p->getStats();

			for (unsigned i = 0; i < 6; ++i)
			{
				stats[i] += stuffStats[i];
			}
		}
	}

	return stats;
}

const Object* Inventory::getStuff(unsigned stuffIndex) const{

	assert(stuffIndex < stuff.size());

	return static_cast<const Object*>(stuff[stuffIndex]);
}

const Object* Inventory::getObject(unsigned bagIndex) const{

	assert(bagIndex < bag.size());

	return static_cast<const Object*>(bag[bagIndex]);
}

std::string Inventory::getBasicStatName() const {
    return basicStat.getName();
}

void Inventory::display(){

	std::cout << "Inventaire d'" << basicStat.getName() << " :" << std::endl;
    std::cout << std::endl;

	std::cout << "      Equipement :" << std::endl;
    std::cout << std::endl;

	for (auto p : stuff){
		if (p)
		std::cout << "          "  << p->getId() << std::endl;
	}

    std::cout << std::endl;
	std::cout << "      Sacoche:" << std::endl;
    std::cout << std::endl;
	for (auto p : bag){
		if (p)
		std::cout << "          " << p->getId() << std::endl;
	}
}

void Inventory::swapStuffBag(unsigned stuffIndex, unsigned bagIndex){

	Object *temp {stuff[stuffIndex]};
	stuff[stuffIndex] = bag[bagIndex];
	bag[bagIndex] = temp;
}

bool Inventory::isItInInventory(unsigned id, unsigned number) {
    for(auto p : bag) {
        if (p) {
            if(p->getId() == id && p->getObjectNumber() == number){
                return true;
            }
        }
    }
    return false;
}

bool Inventory::isEmpty() {
    for(auto p : bag){
        if(p)
            return false;
    }
    return true;
}