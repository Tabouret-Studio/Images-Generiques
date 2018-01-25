//
//  UIButton.cpp
//  Xcode
//
//  Created by Valentin Dufois on 25/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "UIButton.hpp"

#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Elements/Mesh.hpp"
#include "Elements/Font.hpp"
#include "Elements/Image.hpp"
#include "Core/AppObject.hpp"
#include "Utils/DrawCursor.hpp"

//Default colors
#define BUTTON_TEXT_IDLE_COLOR glm::vec4(0, 0, 0, 1)
#define BUTTON_TEXT_SELECTED_COLOR glm::vec4(1, 1, 1, 1)

UIButton::UIButton(const UIButtonType &type, const uint &posX, const uint &posY, const uint &width, const uint &height):
	m_type(type),
	m_posX(posX),
	m_posY(posY),
	m_width(width),
	m_height(height),
	m_tile(nullptr),
	m_backTile(nullptr),
	m_font(nullptr),
	m_textAlign(UI_TEXT_CENTER)
{
	refreshGeometry();
}

void UIButton::setTextures(const GLuint &idleTexture, const GLuint &activeTexture)
{
	m_idleTexture = idleTexture;
	m_activeTexture = activeTexture;
}

void UIButton::setDimensions(const float &width, const float &height)
{
	m_width = width;
	m_height = height;

	refreshGeometry();
}

void UIButton::setPosition(const float &posX, const float &posY)
{
	m_posX = posX;
	m_posY = posY;

	refreshGeometry();
}

void UIButton::setFont(Font * font, const float &fontSize)
{
	m_font = font;
	m_fontSize = fontSize;

	m_font->loadSize(fontSize);
}

void UIButton::setCaptionAlign(const UIButtonTextAlign &alignment)
{
	m_textAlign = alignment;
}

void UIButton::setCaption(const std::string &caption)
{
	if(m_caption == caption)
		return;

	m_caption = caption;

	m_tile = m_font->genCaption(m_caption, m_fontSize);
	m_tile->applyCursor();
	m_tile->generate();

	//Calculate caption position
	float posX = m_posX;
	float posY = m_posY + (m_height - m_fontSize);

	switch(m_textAlign)
	{
		case UI_TEXT_LEFT: posX += m_tile->getDimensions().x / 2; break;
		case UI_TEXT_CENTER: posX += m_width / 2; break;
		case UI_TEXT_RIGHT: posX += m_width - m_tile->getDimensions().x / 2; break;
	}

	std::cout << glm::to_string(m_tile->getDimensions()) << std::endl;

	m_tile->getCursor()->reset()->translate(posX, posY, 0);
	refreshTextColor();
}

void UIButton::select()
{
	m_selected = true;
	refreshTextColor();
}

void UIButton::deSelect()
{
	m_selected = false;
	refreshTextColor();
}

void UIButton::print()
{
	//Shall we display it or not ?
	if(!m_display)
		return;

	if(m_type == UI_BUTTON_GRAPHIC)
	{
		//Set button texture according to state
		if(isSelected())
			m_tile->setTexture(m_activeTexture);
		else
			m_tile->setTexture(m_idleTexture);
	}

	//Display item
	m_tile->render();

	if(m_type == UI_BUTTON_TEXT && isSelected())
		m_backTile->render();
}

void UIButton::refreshGeometry()
{
	switch(m_type)
	{
		case UI_BUTTON_GRAPHIC:

			m_tile = App->ressourcesEngine->gen2DTile(m_posX, m_posY, m_width, m_height);
			m_tile->generate();
			m_tile->getCursor()->translate(m_posX, m_posY, 0);

			break;
		case UI_BUTTON_TEXT:

			m_backTile = App->ressourcesEngine->gen2DTile(m_posX + m_width / 2, m_posY - m_height * 0.31, m_width, m_height * 1.25);
			m_backTile->setColor(BUTTON_TEXT_IDLE_COLOR);
			m_backTile->generate();

			break;
	}
}

void UIButton::refreshTextColor()
{
	if(m_tile == nullptr)
		return;

	if(isSelected())
		m_tile->setColor(BUTTON_TEXT_SELECTED_COLOR);
	else
		m_tile->setColor(BUTTON_TEXT_IDLE_COLOR);

	m_tile->generate();
}
