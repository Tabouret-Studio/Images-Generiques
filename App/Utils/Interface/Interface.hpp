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

////////////
//PARAMETERS
#define INTERFACE_KEYBOARD_THRESHOLD 80
#define INTERFACE_MOUSE_THRESHOLD 1000

enum InterfaceInteractionsType
{
	INTERFACE_INTERACTIONS_MOUSE,
	INTERFACE_INTERACTIONS_KEYBOARD
};

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
	 Set the interface interactions behaviour
	 INTERFACE_INTERACTIONS_MOUSE - Interact with the mouse
	 INTERFACE_INTERACTIONS_KEYBOARD - Interact with the keyboard

	 @warning Multiple interfaces with keyboard interactions at the same time
	 will all receive the exact same keyboard informations. Meaning you may
	 end up with multiple interactions happening at the same time

	 @param interactionsFormat Behaviour
	 */
	void setInteractionFormat(const InterfaceInteractionsType &interactionsFormat) { m_interactionsFormat = interactionsFormat; };

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

	/**
	 Return all the UIElements stored in the interface

	 @return UIElement vector
	 */
	std::vector<UIElement *> * getElements() { return &m_items; };

	~Interface();

private:

	InterfaceInteractionsType m_interactionsFormat = INTERFACE_INTERACTIONS_KEYBOARD;

	std::vector<UIElement *> m_items;
	UIElement * m_currentItem;

	//Tempo moves to prevent sliding
	uint32_t m_lastAction;

	int m_waitBeforeExecute = 3;

	void keyboardInteractions();
	void mouseInteractions();
};

#endif /* Interface_hpp */
