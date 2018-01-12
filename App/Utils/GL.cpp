//
//  GL.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../main.hpp"

namespace GL
{
	GLuint buildVAO(const GLuint &vbo)
	{
		//Create and bind VAO
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//Define vertice properties array hooks
		const GLuint VERTEX_ATTR_POSITION = 1;
		const GLuint VERTEX_ATTR_COLOR = 2;
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
		glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

		//Bind given VBO
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//Specify vertice properties positions

		/**
		 Tell OpenGL where to find data for each vertice passed

		 @param VERTEX_ATTR_POSITION To which hook the data must be linked
		 @param 2 The number of variable in the data (vec2 -> 2)
		 @param GL_FLOAT The type of variables
		 @param GL_FALSE do not touch
		 @param Vertex2DColor The data
		 @return The offset (if needed)
		 */
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), 0);
		glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *) offsetof(Vertex2DColor, color));

		//Unbind everything
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return vao;
	}
}
