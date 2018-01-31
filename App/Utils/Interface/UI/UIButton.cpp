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
	m_tile(nullptr),
	m_backTile(nullptr),
	m_font(nullptr),
	m_textAlign(UI_TEXT_CENTER)
{
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;

	if(m_type == UI_BUTTON_GRAPHIC)
		refreshGeometry();
}

void UIButton::setTextures(const GLuint &idleTexture, const GLuint &activeTexture)
{
	m_idleTexture = idleTexture;
	m_activeTexture = activeTexture;
}

void UIButton::setTextures(const rId &idleTexture, const rId &activeTexture)
{
	Image * idle = *App->ressourcesEngine->getAsset(idleTexture);
	m_idleTexture = idle->getTextureID();

	Image * selected = *App->ressourcesEngine->getAsset(activeTexture);
	m_idleTexture = selected->getTextureID();
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
	setTextPosition();
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

void UIButton::setTextColors(const glm::vec4 &idleColor, const glm::vec4 &selectedColor)
{
	m_idleColor = idleColor;
	m_selectedColor = selectedColor;

	refreshTextColor();
}

void UIButton::setBackColors(const glm::vec4 &idleColor, const glm::vec4 &selectedColor)
{
	m_backIdleColor = idleColor;
	m_backSelectedColor = selectedColor;

	refreshTextColor();
}

void UIButton::setCaption(const std::string &caption)
{
	if(m_caption == caption)
		return;

	m_caption = caption;

	m_tile = m_font->genCaption(m_caption, m_fontSize);
	m_tile->applyCursor();
	m_tile->generate();

	setTextPosition();

	refreshGeometry();
	refreshTextColor();
}

void UIButton::setTextPosition()
{
	//Calculate caption position
	float posX = m_posX;
	float posY = m_posY + (m_height - m_fontSize);

	switch(m_textAlign)
	{
		case UI_TEXT_LEFT: posX += m_tile->getDimensions().x / 2.f + m_width * 0.01f; break;
		case UI_TEXT_CENTER: posX += m_width / 2; break;
		case UI_TEXT_RIGHT: posX += m_width - m_tile->getDimensions().x / 2; break;
	}

	m_tile->getCursor()->reset()->translate(posX, posY, 0);
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

	if(m_type == UI_BUTTON_TEXT)
	{
		glm::vec4 backTileColor;

		if(isSelected())
			backTileColor = m_backSelectedColor;
		else
			backTileColor = m_backIdleColor;

		if(backTileColor.a == 0)
			return;

		m_backTile->setColor(backTileColor);
		m_backTile->generate();
		m_backTile->render();
	}
}

void UIButton::refreshGeometry()
{
	switch(m_type)
	{
		case UI_BUTTON_GRAPHIC:

			delete m_tile;

			m_tile = App->ressourcesEngine->gen2DTile(m_posX, m_posY, m_width, m_height);
			m_tile->generate();
			m_tile->getCursor()->translate(m_posX, m_posY, 0);

			break;
		case UI_BUTTON_TEXT:

			delete m_backTile;

			m_backTile = App->ressourcesEngine->gen2DTile(m_posX + m_width / 2, m_posY - m_height * 0.31, m_width, m_height * 1.25);
			m_backTile->generate();

			setTextPosition();

			break;
	}
}

void UIButton::refreshTextColor()
{
	if(m_tile == nullptr)
		return;

	if(isSelected())
		m_tile->setColor(m_selectedColor);
	else
		m_tile->setColor(m_idleColor);

	m_tile->generate();
}

UIButton::~UIButton()
{
	delete m_tile;
	delete m_backTile;
}
