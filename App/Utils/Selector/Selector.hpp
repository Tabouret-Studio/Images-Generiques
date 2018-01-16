//
//  Selector.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Selector_hpp
#define Selector_hpp

//////////////////////
//Forward declarations
class Item;

#include <iostream>
#include <vector>
#include <cstdint>

class Selector
{
public:

	Selector();

	/**
	 Add an item to the selector

	 @param newItem Add a new item to the selector
	 */
	void addItem(Item * newItem);

	/**
	 Execute interactions in the selector
	 */
	void execute();

    /**
     Render the selector (its items)
     */
    void render();

	/**
	 Move the cursor to the given item

	 @param item Item to select
	 */
	void moveCursor(Item * item);

	~Selector();

private:

	std::vector<Item *> m_items;
	Item * m_currentItem;

	//Tempo moves to prevent sliding
	uint32_t m_lastAction;

	int m_waitBeforeExecute = 3;
};

#endif /* Selector_hpp */
