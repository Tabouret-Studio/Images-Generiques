//
//  Interface.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Interface.hpp"

#include "UIElement.hpp"

#include "Core/AppObject.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

Interface::Interface():
	m_currentItem(nullptr),
	m_lastAction(0)
{}

void Interface::addItem(UIElement * newItem)
{
	m_items.push_back(newItem);

	if(m_items.size() == 1 && m_interactionsFormat == INTERFACE_INTERACTIONS_KEYBOARD)
	{
		newItem->select();
		m_currentItem = newItem;
		return;
	}

	newItem->deSelect();
}

void Interface::execute()
{
	if(m_waitBeforeExecute > 0)
	{
		m_waitBeforeExecute--;
		return;
	}

	//Tempo between action (.08s)
	if(SDL_GetTicks() - m_lastAction < INTERFACE_KEYBOARD_THRESHOLD && m_interactionsFormat == INTERFACE_INTERACTIONS_KEYBOARD)
	{
		App->appEngine->flushKeys();
		return;
	}

	//Move
	if(m_interactionsFormat == INTERFACE_INTERACTIONS_KEYBOARD)
		keyboardInteractions();
	else if(m_interactionsFormat == INTERFACE_INTERACTIONS_MOUSE)
		mouseInteractions();
}

void Interface::keyboardInteractions()
{
	if(App->appEngine->getKeys().DOWN)
		return moveCursor(m_currentItem->getBottomNeighboor());

	if(App->appEngine->getKeys().UP)
		return moveCursor(m_currentItem->getTopNeighboor());

	if(App->appEngine->getKeys().RIGHT)
		return moveCursor(m_currentItem->getRightNeighboor());

	if(App->appEngine->getKeys().LEFT)
		return moveCursor(m_currentItem->getLeftNeighboor());

	//Do something
	if(App->appEngine->getKeys().ENTER)
	{
		m_lastAction = SDL_GetTicks();
		return m_currentItem->action();
	}
}

void Interface::mouseInteractions()
{
	for(UIElement * element : m_items)
	{
		glm::vec2 mousePos = App->appEngine->getMouse().pos;

		glm::vec2 elPos = element->getPosition();
		glm::vec2 elDim = element->getDimensions();

		if(mousePos.x > elPos.x && mousePos.x < (elPos.x + elDim.x) && mousePos.y > (elPos.y - elDim.y) && mousePos.y < (elPos.y))
		{
			moveCursor(element);

			//Do something
			if(App->appEngine->getMouse().leftBtn)
			{
				element->action();
				App->appEngine->flushMouse();
			}
		}
		else
			element->deSelect();
	}
}

void Interface::render()
{
	App->renderEngine->setProjection2D();

	for(std::vector<UIElement *>::iterator el = m_items.begin(); el != m_items.end(); ++el)
        (*el)->print();
}

void Interface::moveCursor(UIElement * item)
{
	if(item == nullptr)
		return;
    
    if(!item->isShown())
        return;

	if(!item->isSelectable())
		return;

	if(m_interactionsFormat == INTERFACE_INTERACTIONS_KEYBOARD)
		m_lastAction = SDL_GetTicks();

	if(m_currentItem != nullptr)
		m_currentItem->deSelect();

	item->select();

	m_currentItem = item;
}

Interface::~Interface()
{
	for(std::vector<UIElement *>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
        delete (*it);
		(*it) = nullptr;
	}
}
