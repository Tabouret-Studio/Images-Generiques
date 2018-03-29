//
//  ProtocolRenderer.hpp
//  Xcode
//
//  Created by Valentin Dufois on 26/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ProtocolRenderer_hpp
#define ProtocolRenderer_hpp

//////////////////////
//Forward declarations
class Font;
class Mesh;
class Interface;
class UIButton;
class InstructionsProtocol;

#include "Scene.hpp"
namespace Scenes
{
	class ProtocolRenderer: public Scene
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
		~ProtocolRenderer();

		/**
		 Set the protocol to be used by this scene

		 @param protocolName Name of the protocol
		 */
		void setProtocol(const std::string &protocolName) { m_protocolName = protocolName; };

	private:

		//Elements
		std::vector<UIButton *> m_buttons;

		VectorImage * m_svg = nullptr;
		Font * m_font;
		float m_zoomLevel;

		Mesh * m_displayMesh = nullptr;
		Mesh * m_protocolCaption;

		std::string m_protocolName;
		InstructionsProtocol * m_protocol;

		//Methods
		void updateInterfaceDimensions();

		void executeProtocol();
	};
}


#endif /* ProtocolRenderer_hpp */
