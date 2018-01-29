//
//  Interface.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

//////////////////////
//Forward declarations
class UIElement;

#include <iostream>
#include <vector>
#include <cstdint>

class Interface
{
public:

	Interface();

	/**
	 Add an item to the Interface

	 @param newItem Add a new item to the Interface
	 */
	void addItem(UIElement * newItem);

	/**
	 Execute interactions in the Interface
	 */
	void execute();

    /**
     Render the Interface (its items)
     */
    void render();

	/**
	 Move the cursor to the given item

	 @param item Item to select
	 */
	void moveCursor(UIElement * item);

	std::vector<UIElement *> * getElements() { return &m_items; };

	~Interface();

private:

	std::vector<UIElement *> m_items;
	UIElement * m_currentItem;

	//Tempo moves to prevent sliding
	uint32_t m_lastAction;

	int m_waitBeforeExecute = 3;
};

#endif /* Interface_hpp */
