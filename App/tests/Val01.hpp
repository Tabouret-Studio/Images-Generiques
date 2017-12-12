//
//  Val01.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Val01_hpp
#define Val01_hpp

#include "../main.hpp"

namespace Tests
{
	class Val01: public Test
	{
	public:
		void setup();
		void render();

	private:
		int m_points;

		GLuint m_vbo;
		GLuint m_vao;
	};
}

#endif /* Val01_hpp */
