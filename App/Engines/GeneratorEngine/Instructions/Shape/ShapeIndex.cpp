//
//  ShapeIndex.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeIndex.hpp"
#include "Core/AppObject.hpp"
#include <math.h>

Instruction * ShapeIndex::get()
{
	return new ShapeIndex();
}

std::vector<VectorImage *> ShapeIndex::execute(std::vector<VectorImage *> &vectorImages)
{

	// Dimensions d'un tracé
	float dimx,dimy;
	// Espacement entre chaque courbe
	float pas_x=App->getWidth()/20,pas_y=App->getHeight()/20;
	
	std::vector<Shape> *shapes,buffer;
	std::vector<VectorImage*> resultat;

	//std::cout<<"pas x et y: "<<pas_x<<" "<<pas_y<<std::endl;
	// Coordonnées: 0,0 pour top-left corner, app-width,0 pour top-right corner
	glm::vec3 lastPos(0, 0, 0);

	// A noter: des ajustements le render de la scène sont à prévoir
	for(VectorImage* svg:vectorImages){

		shapes=svg->getShapes();
		for(Shape shape : *shapes)
		{
			//std::cout<<"last pos"<<lastPos.x<<" "<<lastPos.y<<std::endl;
	
			// Si on dépasse l'écran, retour à la ligne -> saut en y
			if (lastPos.x+pas_x>App->getWidth())
			{
				lastPos.x=0;
				lastPos.y+=pas_y;
			}
			shape.getCursor()->reset();
			dimx=abs(shape.getBoundsMax().x-shape.getPosition().x);
			dimy=abs(shape.getBoundsMax().y-shape.getPosition().y);
	
			// On scale selon la dimension la plus grande
			if (dimx>dimy){
				shape.getCursor()->scale(pas_x/3/dimx,pas_x/3/dimx,1);
			}else{
				shape.getCursor()->scale(pas_y/3/dimy,pas_y/3/dimy,1);
			}
			shape.applyCursor();
	
			// Déplacement, ATTENTION, en deux temps pour des coordonnées de points refreshed
			shape.move(lastPos);
			shape.move(lastPos-(shape.getBoundsMax()-shape.getPosition())/2);
	
			lastPos.x += pas_x;
	
			buffer.push_back(shape);
		}
		
		// L'instruction est elle réductrice ?
		// Le protocole de la scène s'applique sur l'ensemble m_svg, et suivant l'instruction, on peut n'avoir plus qu'une seule image
		resultat.push_back(new VectorImage(buffer));
		// VIDER LA SHAPE avant d'opérer un nouveau svg
		// fuites ? getpaths() modifie t'il l'attrib ??
		buffer.clear();
		
	}
	return resultat;
	
}
