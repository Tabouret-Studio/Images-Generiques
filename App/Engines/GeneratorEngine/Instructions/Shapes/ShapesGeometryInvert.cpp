#include "ShapesGeometryInvert.hpp"
#include <algorithm>

Instruction * ShapesGeometryInvert::get()
{
	return new ShapesGeometryInvert();
}

std::vector<VectorImage *> ShapesGeometryInvert::execute(std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();

	Shape shape;

	glm::vec3
	symline, // axe de symétrie
	starthandle,endhandle, // vecteur poigné
	starthandleprojected,endhandleprojected, // projeté des vecteurs poigné sur symline 
	starthandlegap,endhandlegap, // vecteur décrivant la projection opérée
	starthandlesym,endhandlesym; // coordonné de la symétrie


	for(Bezier path : paths)
	{
		path.applyCursor();
		starthandle=path.getStartHandle()-path.getStartPoint();
		endhandle=path.getEndHandle()-path.getEndPoint();
		symline=glm::normalize(path.getEndPoint()-path.getStartPoint());
		
		starthandleprojected=glm::dot(symline,starthandle)*symline;
		starthandlegap=(path.getStartPoint()+starthandleprojected)-path.getStartHandle();
		starthandlesym=path.getStartHandle()+2*starthandlegap;

		endhandleprojected=glm::dot(symline,endhandle)*symline;
		endhandlegap=(path.getEndPoint()+endhandleprojected)-path.getEndHandle();
		endhandlesym=path.getEndHandle()+2*endhandlegap;

		path= Bezier(path.getStartPoint(),starthandlesym,
			endhandlesym,path.getEndPoint()
		);
		path.applyCursor();

		shape << path;
	}

	return {new VectorImage(shape)};
}
