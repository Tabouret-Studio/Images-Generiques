//
//  Core.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include "../main.hpp"

class Core
{
public:
	/**
	 Init the required components of the app
	 */
	void ignite();

	/**
	 Main loop of the app
	 */
	void main();

	void setup();
	void renderer();

private:

	GLuint m_vbo;
	GLuint m_vao;

};

#endif /* Core_hpp */
