#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

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
		 * @param bagIndex Bag index of the object to equip
		 */
		void equip(unsigned bagIndex);

		/**
		 * @brief unequips object accroding to it's stuff index
		 * @param stuffIndex Bag index of the object to unequip
		 */
		void unequip(unsigned stuffIndex);

		/**
		 * @brief Add an object to the bag inventory
		 * @param id Object id
		 * @param objectNb Object Number, by default at 1
		 */
        void addObject(unsigned id, unsigned objectNb = 1);

        /**
         * @brief Add an object to the bag inventory
         * @param id Object id
         * @param objectNb Object Number, by default at 1
         * @return Return Object number not added
         */
        unsigned addObjectNb(unsigned id, unsigned objectNb = 1);

        /**
         * @brief remove an object according to it's index
         * @param bagIndex Index of the bag inventory to remove
         * @return unsigned Number of object removed
         */
        unsigned removeObject(unsigned bagIndex);

        /**
         * @brief remove an object in inventory according to it id and number
         * @param id Object id
         * @param objectNb Object number
         */
        unsigned removeObject(unsigned id, unsigned objectNb);


        /**
         * @brief Return the number of an object according its id
         * @param id Object id
         * @return unsigned Number of obect count in the inventory
         */
        unsigned getNumber(unsigned id) const;

        /**
         * @brief swap the position of two objects in the bag inventory according their index
         * @param bagIndex1 First bag index
         * @param bagIndex2 Second bag index
         */
        void swapBagBag(unsigned bagIndex1, unsigned bagIndex2);

		/**
		 * @brief gets the stats of all inventory stats and entity basic stats
		 * @return std::vector<int> containing all the stats of stuff + entity basic stats
		 */
		std::vector<int> getAllStats() const;

		/**
		 * @brief Return a reference of a stuff Object according its index
		 * @param stuffIndex Stuff index
		 * @return Object* A reference on Object class
		 */
		const Object* getStuff(unsigned stuffIndex) const;

        /**
         * @brief Return a reference of a bag Object according its index
         * @param bagIndex Bag index
         * @return Object* A reference on Object class
         */
		const Object* getObject(unsigned bagIndex) const;

		/**
		 * @brief Return if inventory contain an object according its id and Number
		 * @param unsigned Object id
		 * @param unsigned Object number
		 * @return boolean If object find with right number or more
		 */
		bool isItInInventory(unsigned, unsigned);

		/**
		 * @brief Test if bag Inventory is empty
		 * @return boolean
		 */
        bool isEmpty();

        /**
         * @brief Test if bag Inventory is full
         * @return boolean
         */
        bool isFull();

        /**
         * @brief Return Id of inventory owner
         * @return unsigned Id of owner
         */
        unsigned getBasicStatId() const;

        /**
         * @brief Return Name of Inventory owner
         * @return std::string Invenotry's owner name
         */
		std::string getBasicStatName() const;

		/**
		 * @brief display for debug purpose
		 */
		void display();

	private:

        /**
         * @brief Swap an object between stuff and bag inventory according their index
         * @param stuffIndex Stuff index
         * @param bagIndex Bag index
         */
		void swapStuffBag(unsigned stuffIndex, unsigned bagIndex);

		Object basicStat;
		std::vector<Object*> stuff;
		std::vector<Object*> bag;
};

#endif // INVENTORY_H
