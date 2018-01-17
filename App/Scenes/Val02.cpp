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

		//Load font
		rId fontID = App->ressourcesEngine->loadAsset("Joystix.ttf", FONT);
		Font * font = *App->ressourcesEngine->getAsset(fontID);
		font->setHeight(20);
		font->generate();

		Item * text;
		float factor;
		int posX, posY;
		Mesh * mesh;
		glm::vec2 dimensions;

		m_mesh = new Mesh();

		int j = 0;

		for(Shape shape : m_svg->getShapes())
		{
			std::vector<Bezier> paths = shape.getPaths();

			int i = 0;

			text = new Item(ITEM_TEXT, 105, 15, 0, 0, nullptr);
			text->setFont(font, "Shape " + std::to_string(0+1));

			m_interface.addItem(text);

			for(Bezier path : paths)
			{
				path.getCursor()->setMatrix(glm::mat4(1.0));

				dimensions = path.getDimensions();

				if(dimensions.x > dimensions.y)
					factor = 50.0 / dimensions.x;
				else
					factor = 50.0 / dimensions.y;

				posX = 35 + (70 * (i % 5)) + 400 * j;
				posY = 65 + (70 * (i / 5));

				path.getCursor()->translate(posX, posY, 0)->scale(factor, factor, 0);
				path.applyCursor();

				*m_mesh << path.getMesh();

				++i;
			}

			++j;
		}

		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val02::execute()
	{
		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val02::render()
	{
		App->renderEngine->render(m_mesh, m_mesh->getCursor());

		//m_interface.render();
	}
}
