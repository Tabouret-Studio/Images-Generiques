//
//  Val02.hpp
//  Xcode
//
//  Created by Valentin Dufois on 17/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Val02_hpp
#define Val02_hpp

//////////////////////
//Forward declarations
class Mesh;
class VectorImage;

#include "Scene.hpp"
#include "Utils/MeshGroup.hpp"

namespace Scenes
{
	class Val02: public Scene
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
		~Val02() {};

	private:

		//Elements
		VectorImage * m_svg;
		Mesh * m_fullImage;
		MeshGroup m_mGroup;

		//Interface m_interface;
	};
}

#endif /* Val02_hpp */
