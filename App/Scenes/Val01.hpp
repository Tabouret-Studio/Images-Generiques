//
//  Val01.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Val01_hpp
#define Val01_hpp

#include "Scene.hpp"
#include "Engines/RessourcesEngine/Elements/Asset.hpp"

namespace Scenes
{
	class Val01: public Scene
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
		~Val01() {};

	private:

		//Elements
		GLuint m_vbo;
		GLuint m_vao;

		uint m_points;
	};
}

#endif /* Val01_hpp */
