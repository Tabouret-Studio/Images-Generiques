//
//  JSONToVectorImagesImporter.hpp
//  Xcode
//
//  Created by Valentin Dufois on 23/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef JSONToVectorImagesImporter_hpp
#define JSONToVectorImagesImporter_hpp

//////////////////////
//Forward declarations
class VectorImage;

#include "libraries.hpp"

class JSONToVectorImagesImporter
{
public:
	std::vector<VectorImage *> import(const std::string &path);

private:

	glm::mat4 convertMatrix(const nlohmann::json &jsonMat);
};


#endif /* JSONToVectorImagesImporter_hpp */
