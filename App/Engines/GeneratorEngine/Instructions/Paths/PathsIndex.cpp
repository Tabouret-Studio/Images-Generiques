//
//  PathsIndex.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsIndex.hpp"
#include "Core/AppObject.hpp"
#include <math.h>

Instruction * PathsIndex::get()
{
	return new PathsIndex();
}

std::vector<VectorImage *> PathsIndex::execute(const std::vector<VectorImage *> &vectorImages)
{

	// Dimensions d'un tracé
	float dimx,dimy;
	// Espacement entre chaque courbe
	float pas_x=App->getWidth()/20,pas_y=App->getHeight()/20;
	
	std::vector<Bezier> paths;
	Shape shape;
	std::vector<VectorImage*> resultat;

	//std::cout<<"pas x et y: "<<pas_x<<" "<<pas_y<<std::endl;
	// Coordonnées: 0,0 pour top-left corner, app-width,0 pour top-right corner
	glm::vec3 lastPos(pas_x/2, 0, 0);

	// A noter: des ajustements le render de la scène sont à prévoir
	for(VectorImage* svg:vectorImages){

		paths=svg->getBeziers();
		for(Bezier path : paths)
		{
			//std::cout<<"last pos"<<lastPos.x<<" "<<lastPos.y<<std::endl;
	
			// Si on dépasse l'écran, retour à la ligne -> saut en y
			if (lastPos.x+pas_x>App->getWidth())
			{
				lastPos.x=pas_x/2;
				lastPos.y+=pas_y;
			}
			path.getCursor()->reset();
			dimx=abs(path.getEndPoint().x-path.getStartPoint().x);
			dimy=abs(path.getEndPoint().y-path.getStartPoint().y);
	
			// On scale selon la dimension la plus grande
			if (dimx>dimy){
				path.getCursor()->scale(pas_x/2/dimx,pas_x/2/dimx,1);
			}else{
				path.getCursor()->scale(pas_y/2/dimy,pas_y/2/dimy,1);
			}
			path.applyCursor();
	
			// Déplacement, ATTENTION, en deux temps pour des coordonnées de points refreshed
			path.move(lastPos);
			path.move(lastPos-(path.getPoint(0.5)-path.getStartPoint()));
	
			lastPos.x += pas_x;
	
			shape << path;
		}
		
		// L'instruction est elle réductrice ?
		// Le protocole de la scène s'applique sur l'ensemble m_svg, et suivant l'instruction, on peut n'avoir plus qu'une seule image
		resultat.push_back(new VectorImage(shape));
		std::cout<<"shape size: "<<shape.getPaths().size()<<std::endl;

		// VIDER LA SHAPE avant d'opérer un nouveau svg
		// fuites ? getpaths() modifie t'il l'attrib ??
		shape=Shape();
		
	}
	return resultat;
	
}
