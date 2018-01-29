#include "PathsLinearAlizer.hpp"

Instruction * PathsLinearAlizer::get()
{
	return new PathsLinearAlizer();
}

std::vector<VectorImage *> PathsLinearAlizer::execute(const std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();

	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	for(Bezier path : paths)
	{
		path.applyCursor();
		path= Bezier(path.getStartPoint(),path.getEndPoint(),path.getStartPoint(),path.getEndPoint());
		shape << path;
	}

	return {new VectorImage(shape)};
}
