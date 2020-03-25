#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>

#include <iostream>

#include "Object.h"

class Inventory
{
	public:
		
		Inventory() = default;
		Inventory(unsigned idBasicStat, unsigned stuffSize, unsigned bagSize);
		~Inventory();
		
		void equip(unsigned bagIndex);
		void unequip(unsigned stuffIndex);
		
		void addObject(unsigned id, unsigned objectNb = 1);
		unsigned removeObject(unsigned bagIndex);
		void swapBagBag(unsigned badIndex1, unsigned badIndex2);
		
		std::vector<int> getAllStats() const;
		const Object* getStuff(unsigned stuffIndex) const;
		const Object* getObject(unsigned bagIndex) const;
		
		void display();
		
	private:
	
		void swapStuffBag(unsigned stuffIndex, unsigned bagIndex);
	
	private:
		
		Object basicStat;
		std::vector<Object*> stuff;
		std::vector<Object*> bag;
};

#endif // INVENTORY_H
