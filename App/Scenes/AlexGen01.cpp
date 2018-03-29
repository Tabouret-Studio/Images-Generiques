#include "AlexGen01.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Mesh.hpp"
#include "Elements/Font.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Exporters/VectorImagesToJSONExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONToVectorImagesImporter.hpp"

#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"

namespace Scenes
{
	void AlexGen01::load()
	{
		Scene * scene = new AlexGen01();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void AlexGen01::init()
	{
		m_zoomLevel = 1;

		//Loading
		rId svgID = App->ressourcesEngine->loadAsset("handComputer.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		/*rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		Font * font = *App->ressourcesEngine->getAsset(fontID);

		m_svg = font->genOutlines("Images Generiques");*/
		
		//m_svg->applyCursor();

		//Instructions
		InstructionsProtocol protocol({
			//"SHAPES_CHAINING"
			//"PATHS_CHAINING"
			//"PATHS_INVERT"
			"SHAPES_ORDER_RANDOMIZER"

		});

		std::vector<VectorImage *> images = {m_svg};
		VectorImage * imageTransformed = protocol.execute(images)[0];

		//Export
		SVGExporter exporter;
		exporter.exportSVG(imageTransformed, "testInstruction");

		//Generate and display Mesh
		//m_mesh = m_svg->getMesh();

		m_mesh = imageTransformed->getMesh();

		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

		glPointSize(1);

		m_mesh->getCursor()
			->reset()->translate(App->getWidth()/2, App->getHeight()/2, 1)->scale(1, 1, 1);

		//m_mesh->getCursor()->reset();
		//m_mesh->applyCursor();
		//m_mesh->getCursor()->rotate(180, 1, 0, 0)->translate(0, 0, (m_svg->getHeight() / 2.f))->scale(10, 10, 1);

	}


	//////////////
	// This is executed every frame before render
	///////////
	void AlexGen01::execute()
	{
		m_zoomLevel += App->appEngine->getMouse().scrollY / 50.f;
		if(m_zoomLevel < 0)
			m_zoomLevel = 0;
	}


	//////////////
	// This is executed every frame at render
	///////////
	void AlexGen01::render()
	{
		App->renderEngine->setProjection2D();
		m_mesh->getCursor()->reset()
			->translate(App->getWidth()/2, App->getHeight()/2, 0)->scale(m_zoomLevel, m_zoomLevel, 0);

		m_mesh->render();

	}
}
