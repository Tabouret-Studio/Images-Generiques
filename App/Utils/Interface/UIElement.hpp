//
//  UIElement.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "libraries.hpp"
#include <iostream>

class UIElement
{
public:

	UIElement():
		m_display(true),
		m_selected(false),
		m_selectable(true),
		m_topItem(nullptr), m_rightItem(nullptr), m_bottomItem(nullptr), m_leftItem(nullptr), m_callback(nullptr) {};

	/**
	 Print the Item
	 */
	virtual void print() = 0;

	/**
	 Set neighboor UIElements
	 Allow interactions with the arrow keys

	 @param top Top Item
	 @param right Right Item
	 @param bottom Bottom Item
	 @param left Left Item
	 */
	void setNeighboors(UIElement * top, UIElement * right, UIElement * bottom, UIElement * left)
	{
		m_topItem = top;
		m_rightItem = right;
		m_bottomItem = bottom;
		m_leftItem = left;
	};

	inline void setTopNeighboor(UIElement * neighboor) { m_topItem = neighboor; };
	inline void setRightNeighboor(UIElement * neighboor) { m_rightItem = neighboor; };
	inline void setBottomNeighboor(UIElement * neighboor) { m_bottomItem = neighboor; };
	inline void setLeftNeighboor(UIElement * neighboor) { m_leftItem = neighboor; };

	/**
	 Set action to execute when enter is pressed on this element

	 @param callback Pointer to function or lambda function
	 */
	inline void setAction(std::function<void()> callback) { m_callback = callback; };

	/**
	 Return the top neighboor

	 @return Top neighboor
	 */
	inline UIElement * getTopNeighboor() { return m_topItem; };

	/**
	 Return the right neighboor

	 @return Right neighboor
	 */
	inline UIElement * getRightNeighboor() { return m_rightItem; };

	/**
	 Return the bottom neighboor

	 @return Bottom neighboor
	 */
	inline UIElement * getBottomNeighboor() { return m_bottomItem; };

	/**
	 Return the left neighboor

	 @return Left neighboor
	 */
	inline UIElement * getLeftNeighboor() { return m_leftItem; };

	/**
	 Tell if Item is selected or not

	 @return true if selected, false otherwise
	 */
	inline bool isSelected() const { return m_selected; };

	/**
	 Mark the item as selected
	 */
	virtual void select() { m_selected = true; };

	/**
	 Mark the item as deselected
	 */
	virtual void deSelect() { m_selected = false; };

    /**
     Tell if the item is shown or not

     @return true if shown, false otherwise
     */
	inline bool isShown() const { return m_display; };
    
	/**
	 Disable the Item
	 */
	void hide() { m_display = false; };
	/**
	 Enable the Item
	 */
	void show() { m_display = true; };

	/**
	 Execute Item action
	 */
	void action()
	{
		if(m_callback == nullptr)
			return;

		m_callback();
	}

	/**
	 Return the dimensions of the element

	 @return The element's dimensions
	 */
	inline glm::vec2 getDimensions() const { return glm::vec2(m_width, m_height); };

	/**
	 Return the position (top left) of the element

	 @return The element's position
	 */
	inline glm::vec2 getPosition() const { return glm::vec2(m_posX, m_posY); };

	/**
	 Set if item can be selected

	 @param selectable True to be able to be selected, false otherwise
	 */
	void setSelectable(const bool &selectable) { m_selectable = selectable; };

	/**
	 Tell if the item can be selected

	 @return True if yes, false otherwise
	 */
	inline bool isSelectable() const { return m_selectable; };

	virtual ~UIElement() = default;

protected:

	//Display properties
	bool m_display;

	//Positionning
	uint m_posX;
	uint m_posY;

	//Dimensions
	uint m_width;
	uint m_height;

	//current state
	bool m_selected;
	bool m_selectable;

	//Neighboors
	UIElement * m_topItem;
	UIElement * m_rightItem;
	UIElement * m_bottomItem;
	UIElement * m_leftItem;

	std::function<void()> m_callback;
};

#endif /* UIElement_hpp */
