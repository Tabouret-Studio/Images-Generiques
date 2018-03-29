//
//  ProtocolsMenu.hpp
//  Xcode
//
//  Created by Valentin Dufois on 24/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ProtocolsMenu_hpp
#define ProtocolsMenu_hpp

//////////////////////
//Forward declarations
class Font;
class Mesh;
class Interface;
class UIButton;

#include "Scene.hpp"
namespace Scenes
{
	class ProtocolsMenu: public Scene
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
		~ProtocolsMenu();

	private:

		//Elements
		Font * m_font;
		Interface * m_interface;

		std::vector<UIButton *> m_buttons;

		float m_fontSize;

		//Methods
		void updateInterfaceDimensions();
	};
}

#endif /* ProtocolsMenu_hpp */
