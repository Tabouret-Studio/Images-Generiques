//
//  vertexColor.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef vertexColor_hpp
#define vertexColor_hpp

#include "../main.hpp"

struct Vertex2DColor
{
	glm::vec2 position;
	glm::vec3 color;

	Vertex2DColor(){}
	Vertex2DColor(glm::vec2 position):position(position), color(glm::vec3(0, 0, 0)){}
	Vertex2DColor(glm::vec2 position, glm::vec3 color):position(position), color(color){}
};

#endif /* vertexColor_hpp */
