//
//  FontOutliner.cpp
//  Xcode
//
//  Created by Valentin Dufois on 28/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "FontOutliner.hpp"

#include "Elements/Vector/Bezier.hpp"
#include "Utils/Utils.hpp"

#include <iostream>

int FontOutliner::MoveToFunction(const FT_Vector *to, void *user)
{
	FontOutliner *self = static_cast<FontOutliner *>(user);

	self->m_lastPoint = glm::vec3(to->x, to->y, 0);

	return 0;
}

int FontOutliner::LineToFunction(const FT_Vector *to, void *user)
{
	FontOutliner *self = static_cast<FontOutliner *>(user);

	glm::vec3 startP(self->m_lastPoint);
	glm::vec3 endP(to->x, to->y, 0);

	glm::vec3 startH(Utils::getIPointBetween(startP, endP, .33f));
	glm::vec3   endH(Utils::getIPointBetween(startP, endP, .66f));

	self->m_letterShape << Bezier(startP, startH, endH, endP);
	self->m_lastPoint = endP;

	return 0;
}

int FontOutliner::ConicToFunction(const FT_Vector *control, const FT_Vector *to, void *user)
{
	FontOutliner *self = static_cast<FontOutliner *>(user);

	glm::vec3 startP(self->m_lastPoint);
	glm::vec3 endP(to->x, to->y, 0);

	glm::vec3   startH(Utils::getIPointBetween(startP, glm::vec3(control->x, control->y, 0), .66));
	glm::vec3   endH(Utils::getIPointBetween(glm::vec3(control->x, control->y, 0), endP, .33));

	self->m_letterShape << Bezier(startP, startH, endH, endP);
	self->m_lastPoint = endP;

	return 0;
}

int FontOutliner::CubicToFunction(const FT_Vector *controlOne, const FT_Vector *controlTwo, const FT_Vector *to, void *user)
{
	FontOutliner *self = static_cast<FontOutliner *>(user);

	glm::vec3 startP(self->m_lastPoint);
	glm::vec3 startH(controlOne->x, controlOne->y, 0);
	glm::vec3   endH(controlTwo->x, controlTwo->y, 0);
	glm::vec3   endP(to->x, to->y, 0);

	self->m_letterShape << Bezier(startP, startH, endH, endP);
	self->m_lastPoint = endP;

	return 0;
}
