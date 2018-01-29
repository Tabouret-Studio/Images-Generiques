//
//  SimpleRenderer.hpp
//  Xcode
//
//  Created by Valentin Dufois on 29/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

//////////////////////
//Forward declarations
class Mesh;

#include "Scene.hpp"

#include "libraries.hpp"

namespace Scenes
{
	class SimpleRenderer: public Scene
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

		void setBounds(const uint &marginLeft, const uint &marginTop, const uint &width, const uint &height);

		void setMesh(Mesh * mesh);

		/**
		 Destructor, used to properly free all the memory used by the scene
		 */
		~SimpleRenderer() {};

	private:

		//Renderwindow positionning
		glm::vec2 m_renderMargin;
		glm::vec2 m_renderDimensions;

		Mesh * m_mesh = nullptr;
	};
}

#endif /* SimpleRenderer_hpp */
