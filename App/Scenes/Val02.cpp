//
//  Val02.cpp
//  Xcode
//
//  Created by Valentin Dufois on 17/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Val02.hpp"

#include "Elements/Vector/Bezier.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Mesh.hpp"
#include "Elements/Font.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

namespace Scenes
{
	void Val02::load()
	{
		Scene * scene = new Val02();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void Val02::init()
	{
		//Load SVG
		rId svgID = App->ressourcesEngine->loadAsset("handComputer.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		//Store full image
		m_fullImage = m_svg->getMesh();
		m_fullImage->generate();

		float factor = std::min(400.0 / m_svg->getDimensions().x, 400.0 / m_svg->getDimensions().y) * 0.9f;

		m_fullImage->getCursor()
			->translate(225, 225, 0)
			->scale(factor, factor, 0);

		//Load font
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Regular.ttf", FONT);
		Font * font = *App->ressourcesEngine->getAsset(fontID);
		font->loadSize(25);

		int posX, posY;
		glm::vec2 dimensions;
		Mesh * textMesh;

		Mesh * pathsMeshs = new Mesh();

		int j = 0;
		int roofLine = 25;

		for(Shape shape : *m_svg->getShapes())
		{
			std::vector<Bezier> paths = *shape.getPaths();

			int i = 0;

			//Gen Shape text
			textMesh = font->genCaption("Shape " + std::to_string(j+1), 25);
			textMesh->getCursor()->translate(175, roofLine, 0);
			textMesh->generate();

			roofLine += 40;

			m_mGroup << textMesh;

			//Parse shape paths
			for(Bezier path : paths)
			{
				path.getCursor()->reset();

				posX = 25 + (100 * (i % 5));
				posY = roofLine + 25 + 100 * (i/5);

				path.getCursor()->translate(posX, posY, 0)/*->scale(factor, factor, 0)*/;
				path.applyCursor();

				*pathsMeshs << path.getMesh();

				++i;
			}

			roofLine += 100 + 100 * (i/5);
			++j;
		}

		pathsMeshs->generate();
		pathsMeshs->setRenderFormat(GL_POINTS);

		m_mGroup << pathsMeshs;
		m_mGroup.getCursor()->translate(450, 0, 0);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val02::execute()
	{
		m_mGroup.getCursor()->translate(0, App->appEngine->getMouse().scrollY * 10, 0);
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val02::render()
	{
		App->renderEngine->setProjection2D();
		m_fullImage->render();
		m_mGroup.render();

	}
}
