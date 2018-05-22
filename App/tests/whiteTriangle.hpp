//
//  whiteTriangle.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef whiteTriangle_hpp
#define whiteTriangle_hpp

#include "../main.hpp"

namespace Tests
{
	class whiteTriangle: public Test
	{
	public:
		void setup();
		void render();

	private:
		GLuint m_vbo;
		GLuint m_vao;
	};
}

#endif /* whiteTriangle_hpp */
