//
//  AssemblageInterface.hpp
//  Xcode
//
//  Created by Valentin Dufois on 29/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef AssemblageInterface_hpp
#define AssemblageInterface_hpp

//////////////////////
//Forward declarations
class Font;
class Interface;
class UIButton;
class InstructionsProtocol;
class VectorImage;
class SimpleRenderer;

#include "libraries.hpp"
#include "Scene.hpp"

#include <vector>
#include <chrono>

namespace Scenes
{
	class AssemblageInterface: public Scene
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
		~AssemblageInterface();

	private:

		//Scene
		glm::vec2 m_workArea;

		//Assets & elements
		Font * m_font = nullptr;
		Interface * m_baseInterface = nullptr;
		UIButton * m_addInstructionBtn = nullptr;
		UIButton * m_playPauseBtn = nullptr;
		UIButton * m_resetBtn = nullptr;
		Interface * m_instructionsInterface = nullptr;
		std::vector<Mesh *> m_lines;
		Mesh * m_vertSeparator;

		SimpleRenderer * m_renderer;

		bool m_reloadList = false;

		//The instructions, stored in a protocol
		InstructionsProtocol * m_protocol = nullptr;

		bool m_playing = true;

		//internal functions
		void generateInstructionList();

		//////////
		//THE LOOP
		void initLoop();
		void resetLoop();
		void protocolLoop();

		void sendToRenderer(VectorImage * vectorImage);

		uint m_nextInstruction = 0;
		std::chrono::steady_clock::time_point m_lastIter;
		Mesh * m_loopCursor = nullptr;
		Mesh * m_workingMesh = nullptr;
		VectorImage * m_workingImage = nullptr;
		//
		//////////

	};
}

#endif /* AssemblageInterface_hpp */
