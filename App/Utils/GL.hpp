//
//  GL.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef GL_hpp
#define GL_hpp

#include "../main.hpp"

namespace GL
{
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
	
	GLuint buildVAO(const std::vector<Vertex2DColor> &vertices, const GLuint &vbo);
}

#endif /* GL_hpp */
