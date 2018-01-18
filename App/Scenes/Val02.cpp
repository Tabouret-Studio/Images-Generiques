//
//  Val02.cpp
//  Xcode
//
//  Created by Valentin Dufois on 17/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Val02.hpp"

#include "Utils/Vector/Bezier.hpp"

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
#include "Engines/RessourcesEngine/Elements/Font.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Selector/Item.hpp"

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
		rId svgID = App->ressourcesEngine->loadAsset("ml.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		//Store full image
		m_fullImage = m_svg->getMesh();
		m_fullImage->generate();

		float factor;

		if(m_svg->getWidth() > m_svg->getHeight())
			factor = 400.0 / m_svg->getWidth();
		else
			factor = 400.0 / m_svg->getHeight();

		m_fullImage->getCursor()
			->translate(225, 225, 0)
			->scale(factor, factor, 0);

		//Load font
		rId fontID = App->ressourcesEngine->loadAsset("Joystix.ttf", FONT);
		Font * font = *App->ressourcesEngine->getAsset(fontID);
		font->setHeight(20);
		font->generate();

		Item * text;
		int posX, posY;
		glm::vec2 dimensions;
		Mesh * textMesh;

		Mesh * pathsMeshs = new Mesh();

		int j;
		int roofLine = 25;

		for(Shape shape : m_svg->getShapes())
		{
			std::vector<Bezier> paths = shape.getPaths();

			int i = 0;

			//Gen Shape text
			textMesh = font->genCaption("Shape " + std::to_string(j+1));
			textMesh->getCursor()->translate(175, roofLine, 0);
			textMesh->generate();

			roofLine += 40;

			m_mGroup << textMesh;

			//Parse shape paths
			for(Bezier path : paths)
			{
				path.getCursor()->setMatrix(glm::mat4(1.0));

				dimensions = path.getDimensions();

				if(dimensions.x > dimensions.y)
					factor = 50.0 / dimensions.x;
				else
					factor = 50.0 / dimensions.y;

				posX = 25 + (70 * (i % 5));
				posY = roofLine + 25 + 70 * (i/5);

				path.getCursor()->translate(posX, posY, 0)->scale(factor, factor, 0);
				path.applyCursor();

				*pathsMeshs << path.getMesh();

				++i;
			}

			roofLine += 70 + 70 * (i/5);
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
		m_fullImage->render();
		m_mGroup.render();

	}
}
