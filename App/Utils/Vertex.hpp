#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#define VERTEX_DEFAULT_COLOR glm::vec4(0, 0, 0, 1)

/**
 Strucure use to communicate vertex information to the GC
 Its main goal is to provide a unified interface to communicate with the GC no matter the type of the element being sent
*/
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;		//Used if Mesh.type = COLORED
	glm::vec2 UV;			//Used if Mesh.type = TEXTURED

	//////////////
	//Constructors

	Vertex() {};

	Vertex(glm::vec3 pos):
		position(pos),
		color(VERTEX_DEFAULT_COLOR) {};

	Vertex(glm::vec3 pos, glm::vec3 aNormal):
		position(pos),
		normal(aNormal),
		color(VERTEX_DEFAULT_COLOR) {};

	Vertex(glm::vec3 pos, glm::vec2 aUV):
		position(pos),
		color(VERTEX_DEFAULT_COLOR),
		UV(aUV) {};

	Vertex(glm::vec3 pos, glm::vec3 aNormal, glm::vec4 aColor):
		position(pos),
		normal(aNormal),
		color(aColor) {};

	Vertex(glm::vec3 pos, glm::vec3 aNormal, glm::vec4 aColor, glm::vec2 aUV):
		position(pos),
		normal(aNormal),
		color(aColor),
		UV(aUV) {};
};

#endif /* VERTEX_HPP */
