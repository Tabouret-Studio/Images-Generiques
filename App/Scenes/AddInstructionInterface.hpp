//
//  AddInstructionInterface.hpp
//  Xcode
//
//  Created by Valentin Dufois on 30/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef AddInstructionInterface_hpp
#define AddInstructionInterface_hpp

//////////////////////
//Forward declarations
class Font;
class Interface;
class UIButton;

#include "Scene.hpp"

#include "libraries.hpp"

#include <vector>
#include <map>

namespace Scenes
{
	////////////////////////////////////
	//Forward declaration (in namespace)
	class AssemblageInterface;

	class AddInstructionInterface: public Scene
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
		 Called when the window is resized
		 */
		void onWindowResized();

		/**
		 Render the scene on the screen
		 */
		void render();

		/**
		 Destructor, used to properly free all the memory used by the scene
		 */
		~AddInstructionInterface();

		void setAssemblageScene(AssemblageInterface * scene) { m_assemblageScene = scene; };

	private:

		//parent scene
		AssemblageInterface * m_assemblageScene;
		bool m_goback = false;

		//Elements
		Font * m_font = nullptr;
		Interface * m_baseInterface = nullptr;
		Interface * m_actionListInterface = nullptr;
		Interface * m_sourceListInterface = nullptr;
		Interface * m_instructionConfirmInterface = nullptr;

		UIButton * m_backButton = nullptr;

		UIButton * m_actionBtn = nullptr;
		UIButton * m_sourceBtn = nullptr;

		Mesh * m_topSeparator = nullptr;
		Mesh * m_bottomSeparator = nullptr;
		Mesh * m_vertSeparator = nullptr;

		uint m_listsLeftMargin;

		std::u16string m_currentSource = u"";
		std::u16string m_currentAction = u"";

		//Lists
		//[ACTION, [SOURCE, ID]]
		std::map<std::u16string, std::map<std::u16string, std::string>> m_instructionsLists;

		void parseInstructions();
		void displayActionsList();
		void displaySourcesList(const std::u16string &action);
		void displayConfirm(const std::u16string &action, const std::u16string &source);
		void addInstructionAndQuit(const std::string &instruction);
	};
}

#endif /* AddInstructionInterface_hpp */
