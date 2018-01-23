//
//  ml2.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "ml2.hpp"

#include "Elements/Vector/Bezier.hpp"
#include "Utils/Vertex.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Selector/Item.hpp"

#include <iostream>

namespace Scenes
{
	void ml2::load()
	{
		Scene * scene = new ml2();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ml2::init()
	{
		//Load SVG
		/*rId svgID1 = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		VectorImage * svg1 = *App->ressourcesEngine->getAsset(svgID1);

		rId svgID2 = App->ressourcesEngine->loadAsset("ml.svg", VECTOR);
		VectorImage * svg2 = *App->ressourcesEngine->getAsset(svgID2);

		//Create new VectorImage
		VectorImage newSvg = VectorImage();

		//Create new shape with Beziers of source img 1
		Shape shape = new Shape(svg1.getBeziers());

		std::vector<glm::vec2> coords2 =*/

		
	}


	//////////////
	// This is executed every frame before render
	///////////
	void ml2::execute()
	{
		float scrollAmount = App->appEngine->getMouse().scrollX/10.0f;
		if(scrollAmount != 0) {
			m_mesh->getCursor()->scale(1+scrollAmount, 1+scrollAmount, 1);
		}
	}


	//////////////
	// This is executed every frame at render
	///////////
	void ml2::render()
	{
		App->renderEngine->render(m_mesh, m_mesh->getCursor());
	}
}
