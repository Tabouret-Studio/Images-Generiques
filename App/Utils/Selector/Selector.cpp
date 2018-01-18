//
//  Selector.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Selector.hpp"

#include "Item.hpp"

#include "Core/AppObject.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

Selector::Selector():
	m_currentItem(nullptr),
	m_lastAction(0)
{}

void Selector::addItem(Item * newItem)
{
	m_items.push_back(newItem);

	if(m_items.size() == 1)
	{
		newItem->select();
		m_currentItem = newItem;
	}
	else
	{
		newItem->deSelect();
	}
}

void Selector::execute()
{
	if(m_waitBeforeExecute > 0)
	{
		m_waitBeforeExecute--;
		return;
	}
	
	if(m_currentItem == nullptr)
		return;

	//Tempo between action (.08s)
	if(SDL_GetTicks() - m_lastAction < 80)
		return App->appEngine->flushKeys();

	if(App->appEngine->getKeys().DOWN)
		return moveCursor(m_currentItem->getBottomNeighboor());

	if(App->appEngine->getKeys().UP)
		return moveCursor(m_currentItem->getTopNeighboor());

	if(App->appEngine->getKeys().RIGHT)
		return moveCursor(m_currentItem->getRightNeighboor());

	if(App->appEngine->getKeys().LEFT)
		return moveCursor(m_currentItem->getLeftNeighboor());

	if(App->appEngine->getKeys().ENTER)
	{
		m_lastAction = SDL_GetTicks();
		return m_currentItem->action();
	}
}

void Selector::render()
{
	App->renderEngine->setProjection2D();

	for(std::vector<Item *>::iterator it = m_items.begin(); it != m_items.end(); ++it)
        (*it)->print();
}

void Selector::moveCursor(Item * item)
{
	if(item == nullptr)
		return;
    
    if(!item->isShown())
        return;

	m_lastAction = SDL_GetTicks();
        
	m_currentItem->deSelect();
	item->select();

	m_currentItem = item;
}

Selector::~Selector()
{
	for(std::vector<Item *>::iterator it = m_items.begin(); it != m_items.end(); ++it)
        delete (*it);
}
