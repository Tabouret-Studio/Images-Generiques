//
//  VectorImagesToJSONExporter.hpp
//  Xcode
//
//  Created by Valentin Dufois on 23/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef VectorImagesToJSONExporter_hpp
#define VectorImagesToJSONExporter_hpp

/////////////////////
//Forward declaration
class VectorImage;
class DrawCursor;

#include "libraries.hpp"

#include <iostream>

class VectorImagesToJSONExporter
{
public:
	void exportJSON(std::vector<VectorImage *> vectorImages, const std::string &path);

private:
	nlohmann::json cursorToJson(DrawCursor * cursor);
};

#endif /* VectorImagesToJSONExporter_hpp */
