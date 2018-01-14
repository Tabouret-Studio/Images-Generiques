//
//  FontImporter.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 28/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "FontImporter.hpp"

#include "libraries.hpp"
#include "Core/AppObject.hpp"
#include "../Elements/Font.hpp"

Asset * FontImporter::getAsset(const std::string &path)
{
	FT_Face face;

	if(FT_New_Face(App->ressourcesEngine->getFTLibrary(), path.c_str(), 0, &face))
	{
		throw std::runtime_error("Could not load font " + path);
	}

	return new Font(face);
}

FontImporter::~FontImporter()
{

}
