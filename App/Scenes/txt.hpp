//
//  txt.hpp
//  Xcode
//
//  Created by Valentin Dufois on 24/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef txt_hpp
#define txt_hpp

//////////////////////
//Forward declarations
class Font;
class Mesh;

#include "Scene.hpp"
namespace Scenes
{
	class txt: public Scene
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
		~txt() {};

	private:

		//Elements
		Font * m_font;
		Mesh * m_mesh;
		Mesh * m_line;
	};
}

#endif /* txt_hpp */
