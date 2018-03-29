//
//  Val01.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Val01.hpp"

#include "Elements/Vector/Bezier.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Font.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Interface/UIElement.hpp"

namespace Scenes
{
	void Val01::load()
	{
		Scene * scene = new Val01();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void Val01::init()
	{
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Regular.ttf", FONT);
		Font * font = *App->ressourcesEngine->getAsset(fontID);

		m_mesh = font->genOutlines(u"Images Génériques")->getMesh(.5f);
		m_mesh->generate();
		m_mesh->getCursor()->translate(App->getWidth()/2, App->getHeight()/2, 0);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val01::execute()
	{
		m_mesh->getCursor()->scale(1.0 + App->appEngine->getMouse().scrollY/10.0, 1.0 + App->appEngine->getMouse().scrollY/10.0, 0);
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val01::render()
	{
		App->renderEngine->setProjection2D();

		App->renderEngine->render(m_mesh, m_mesh->getCursor());
	}
}
