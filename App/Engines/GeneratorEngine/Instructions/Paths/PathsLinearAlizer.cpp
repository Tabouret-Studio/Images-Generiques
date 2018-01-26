#include "PathsLinearAlizer.hpp"

Instruction * PathsLinearAlizer::get()
{
	return new PathsLinearAlizer();
}

std::vector<VectorImage *> PathsLinearAlizer::execute(std::vector<VectorImage *> vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	for(Bezier path : paths)
	{
		path.applyCursor();
		path= Bezier(path.getStartPoint(),path.getEndPoint(),path.getStartPoint(),path.getEndPoint());
		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
