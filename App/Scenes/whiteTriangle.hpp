//
//  whiteTriangle.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef whiteTriangle_hpp
#define whiteTriangle_hpp

#include "Scene.hpp"

namespace Scenes
{
	class whiteTriangle: public ::Scene
	{
	public:
		/**
		 Fast-forward method to instanciate, init and in the scene App
		 */
		static void load();

		/**
		 Initialize the scene
		 */
		void init();

		/**
		 Execute all the actions in the scene
		 */
		void execute();

		/**
		 Render the scene on the screen
		 */
		void render();

		/**
		 Destructor, used to properly free all the memory used by the scene
		 */
		~whiteTriangle() {};

	private:

		//Elements
		GLuint m_vbo;
		GLuint m_vao;
	};
}

#endif /* whiteTriangle_hpp */
