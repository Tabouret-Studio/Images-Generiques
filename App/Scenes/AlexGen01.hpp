#ifndef AlexGen01_hpp
#define AlexGen01_hpp

//////////////////////
//Forward declarations
class Mesh;
class VectorImage;

#include "Scene.hpp"
namespace Scenes
{
	class AlexGen01: public Scene
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
		~AlexGen01() {};

	private:

		//Elements
		VectorImage * m_svg;
		Mesh * m_mesh;
		float m_zoomLevel;
	};
}

#endif /* AlexGen01_hpp */
