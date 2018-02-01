#include "ShapesChaining.hpp"

Instruction * ShapesChaining::get()
{
	return new ShapesChaining();
}

std::vector<VectorImage *> ShapesChaining::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<std::vector<Shape>> imagesShapes;

	for(unsigned int i=0; i<vectorImages.size(); ++i)
	{
		imagesShapes.push_back(vectorImages[i]->getShapes());
	}

	Shape rshape;
	std::vector<Bezier> paths;

	Bezier firstPath = imagesShapes[0][0].getPaths()[0];
	firstPath.applyCursor();
	glm::vec3 currentPos(0, 0, 0);

	for(std::vector<Shape> shapes : imagesShapes)
	{
		for(Shape shape : shapes)
		{
			paths = shape.getPaths();
			for(Bezier path : paths)
			{
				path.getCursor()->reset();
				path.move(currentPos);
				rshape << path;
				currentPos = path.getEndPoint();
			}
		}
	}

	//rshape.getCursor()->setMatrix(imagesShapes[0][0].getCursor()->getMatrix());
	//VectorImage* image = new VectorImage(rshape);
	//image->getCursor()->setMatrix(vectorImages[0]->getCursor()->getMatrix());

	return {new VectorImage(rshape)};

}
