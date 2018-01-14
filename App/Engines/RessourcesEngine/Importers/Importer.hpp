//
//  Importer.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Importer_hpp
#define Importer_hpp

//////////////////////
//Forward declarations
class Asset;

#include <iostream>

class Importer
{
public:
	virtual Asset * getAsset(const std::string &path) = 0;
	virtual ~Importer() {}
};

#include "ImageImporter.hpp"
#include "SoundImporter.hpp"
#include "MeshImporter.hpp"
#include "ShaderImporter.hpp"
#include "FontImporter.hpp"
#include "SVGImporter.hpp"

#endif /* Importer_hpp */
