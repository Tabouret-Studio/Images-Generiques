//
//  Keynote.hpp
//  Xcode
//
//  Created by Valentin Dufois on 25/05/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Keynote_hpp
#define Keynote_hpp

//////////////////////
//Forward declarations
class InstructionsProtocol;
class InstructionParameters;
class VectorImage;
class SimpleRenderer;

#include "libraries.hpp"
#include "Scene.hpp"

#include <vector>
#include <chrono>

namespace Scenes
{
	class Keynote: public Scene
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
		~Keynote();

	private:

		SimpleRenderer * m_renderer;

		bool m_reloadList = false;

		//The instructions, stored in a protocol
		InstructionsProtocol * m_protocol = nullptr;
		InstructionsProtocol * getProtocol();

		bool m_playing = true;

		//////////
		//THE LOOP

		void initLoop();
		void toggleLoop();
		void resetLoop();
		void protocolLoop();


		void sendToRenderer(VectorImage * vectorImage, const uint &pointSize);

		uint m_nextInstruction = 0;
		std::chrono::steady_clock::time_point m_lastIter;
		long m_currentRenderIter;
		Mesh * m_workingMesh = nullptr;
		VectorImage * m_workingImage = nullptr;
		VectorImage * m_savedImage = nullptr;

		//
		//////////

		void applyPathsIndex();
		void applyShapesIndex();

		std::string floatToString(const float &val);
	};
}

#endif /* Keynote_hpp */
