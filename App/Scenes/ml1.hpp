//
//  Val01.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef ml1_hpp
#define ml1_hpp

//////////////////////
//Forward declarations
class Mesh;

#include "Scene.hpp"
#include "Utils/Interface/Interface.hpp"

namespace Scenes
{
	class ml1: public Scene
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
		~ml1() {};

	private:

		//Elements
		Mesh * m_mesh;
	};
}

#endif /* Val01_hpp */
