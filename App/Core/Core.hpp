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

struct Vertex2DColor
{
	glm::vec2 position;
	glm::vec3 color;

	Vertex2DColor(){}
	Vertex2DColor(glm::vec2 position, glm::vec3 color):position(position), color(color){}
};

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


	/**
	 Pause the app to respect 60 fps

	 @param start start of the loop
	 @param end end of the loop
	 */
	void tempo(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end)
	{
		std::chrono::milliseconds elapsed, toWait;

		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		if(elapsed.count() < FRAMERATE)
		{
			toWait = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(FRAMERATE) - elapsed);
			std::this_thread::sleep_for(toWait);
		}
	}
};

#endif /* Core_hpp */
