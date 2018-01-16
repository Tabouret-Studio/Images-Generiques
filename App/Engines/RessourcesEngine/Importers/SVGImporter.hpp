//
//  SVGImporter.hpp
//  Xcode
//
//  Created by Valentin Dufois on 14/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef SVGImporter_hpp
#define SVGImporter_hpp

//Forward declaration
class Asset;

#include "Importer.hpp"

#include "libraries.hpp"

class SVGImporter: public Importer
{
public:
	Asset * getAsset(const std::string &path);

private:
};

#endif /* SVGImporter_hpp */
