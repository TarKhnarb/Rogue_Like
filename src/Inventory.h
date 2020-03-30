#ifndef GAME_INVENTORY_H_INCLUDED
#define GAME_INVENTORY_H_INCLUDED

#include "Object.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <iostream>

class Inventory
{
	public:

		Inventory() = default;
		Inventory(unsigned idBasicStat, unsigned stuffSize, unsigned bagSize);

		~Inventory();

		/**
		 * @brief equips an object with an index from the bag
		 */
		void equip(unsigned bagIndex);

		/**
		 * @brief unequips object accroding to it's index
		 */
		void unequip(unsigned stuffIndex);

        void addObject(unsigned id, unsigned objectNb = 1);
        /**
         * @brief remove an object according to it's index
         */
        unsigned removeObject(unsigned bagIndex);

        /**
         * @brief remove an object in inventory according to id and number of times to be removed
         */
        unsigned removeObject(unsigned id, unsigned objectNb);


        unsigned getNumber(unsigned id) const;

        void swapBagBag(unsigned bagIndex1, unsigned bagIndex2);

		/**
		 * @brief gets the stats of all inventory
		 * @return a vector containing all the stats
		 */
		std::vector<int> getAllStats() const;

		const Object* getStuff(unsigned stuffIndex) const;

		const Object* getObject(unsigned bagIndex) const;

        bool isItInInventory(unsigned, unsigned);
        bool isEmpty();

		std::string getBasicStatName() const;
		/**
		 * @brief display for debug purpose
		 */
		void display();

	private:

		void swapStuffBag(unsigned stuffIndex, unsigned bagIndex);

		Object basicStat;
		std::vector<Object*> stuff;
		std::vector<Object*> bag;
};

#endif // INVENTORY_H
