//
//  GL.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef GL_hpp
#define GL_hpp

#include "libraries.hpp"

namespace GL
{
	/**
	 Generate an OpenGL VBO filled with the given vertex

	 @tparam C the type of data in the vector
	 @param vertices An std::vector
	 @return ID of the newly-created VBO
	 */
	template<class C>
	GLuint buildVBO(const std::vector<C> &vertices)
	{
		//Create and bind VB0
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//Fill VBO with data
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(C), vertices.data(), GL_STATIC_DRAW);

		//Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vbo;
	}

	/**
	 Build an OpenGL VAO with the given VBO

	 @param vbo The VBO containing the vertices
	 @return ID of the newly created VAO
	 */
	GLuint buildVAO(const GLuint &vbo);
}

#endif /* GL_hpp */
