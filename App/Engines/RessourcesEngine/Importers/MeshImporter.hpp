//
//  MeshImporter.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef MeshImporter_hpp
#define MeshImporter_hpp

/////////////////////
//Forward declaration
class Asset;

#include "Importer.hpp"

/**
 Import a 3D element (Blend, OBJ, etc.)
 @warning importation not activated, will return empty mesh
 */
class MeshImporter: public Importer
{
public:
	Asset * getAsset(const std::string &path);

private:

};

#endif /* MeshImporter_hpp */
