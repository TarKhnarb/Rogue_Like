#include "Inventory.h"

Inventory::Inventory(unsigned idBasicStat, unsigned stuffSize, unsigned bagSize) // stuffSize = 0 ou 3
: basicStat {idBasicStat}
, stuff {stuffSize, nullptr}
, bag {bagSize, nullptr}
{ }

Inventory::~Inventory()
{
	for(Object *p : stuff)
	{
		delete p;
		p = nullptr;
	}
	
	for(Object *p : bag)
	{
		delete p;
		p = nullptr;
	}
}

void Inventory::equip(unsigned bagIndex)
{
	assert(bagIndex < bag.size() && bag[bagIndex]);
	
	unsigned stuffIndex;
	switch(bag[bagIndex]->getType())
	{
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
			throw std::runtime_error {"Inventory::equip(" + std::to_string(bagIndex) + ") - Unequipable object"};
			break;
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

void Inventory::addObject(unsigned id, unsigned objectNb)
{
	while (objectNb > 0)
	{
		auto pred = [id] (Object* obj) -> bool { return obj && obj->getId() == id && obj->getObjectNumber() < obj->getMaxStack(); };
		auto found = std::find_if(bag.begin(), bag.end(), pred);
		
		if (found != bag.end())
		{
			objectNb = (*found)->addObjectNumber(objectNb);
		}
		else
		{
			found = std::find(bag.begin(), bag.end(), nullptr);
			if (found == bag.end())
				throw std::runtime_error {"Inventory::addobject(" + std::to_string(id) + ") - Bag is full"};
			
			*found = new Object {id};
			objectNb -= 1;
			objectNb = (*found)->addObjectNumber(objectNb);
		}
	}
}

unsigned Inventory::removeObject(unsigned bagIndex)
{
	assert(bagIndex < bag.size() && bag[bagIndex]);
	
	unsigned result = bag[bagIndex]->getId();
	delete bag[bagIndex];
	bag[bagIndex] = nullptr;
	
	return result;
}

void Inventory::swapBagBag(unsigned bagIndex1, unsigned bagIndex2)
{
	assert(bagIndex1 < bag.size() && bagIndex2 < bag.size());
	
	Object *temp {bag[bagIndex1]};
	bag[bagIndex1] = bag[bagIndex2];
	bag[bagIndex2] = temp;
}

std::vector<int> Inventory::getAllStats() const
{
	std::vector<int> stats (6, 0);
	
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

const Object* Inventory::getStuff(unsigned stuffIndex) const
{
	assert(stuffIndex < stuff.size());
	
	return static_cast<const Object*>(stuff[stuffIndex]);
}

const Object* Inventory::getObject(unsigned bagIndex) const
{
	assert(bagIndex < bag.size());
	
	return static_cast<const Object*>(bag[bagIndex]);
}

void Inventory::display()
{
	std::cout << "INVENTAIRE !!!" << std::endl;
	std::cout << basicStat.getId() << std::endl;
	std::cout << "STUFF:" << std::endl;
	for (auto p : stuff)
	{
		if (p)
		std::cout << p->getId() << std::endl;
		else
		std::cout << "onono" << std::endl;
	}
	std::cout << "BAG:" << std::endl;
	for (auto p : bag)
	{
		if (p)
		std::cout << p->getId() << std::endl;
		else
		std::cout << "onono" << std::endl;
	}
}

void Inventory::swapStuffBag(unsigned stuffIndex, unsigned bagIndex)
{
	Object *temp {stuff[stuffIndex]};
	stuff[stuffIndex] = bag[bagIndex];
	bag[bagIndex] = temp;
}
