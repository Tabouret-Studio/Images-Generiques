#include "ShapesGeometryRandomizer.hpp"
#include "Utils/Utils.hpp"

Instruction * ShapesGeometryRandomizer::get()
{
	return new ShapesGeometryRandomizer();
}

std::vector<VectorImage *> ShapesGeometryRandomizer::execute(std::vector<VectorImage *> &vectorImages)
{
	
	std::vector<Shape> shapes = *vectorImages[0]->getShapes();
	VectorImage* img = new VectorImage();

	for(Shape shape : shapes)
	{
		shape.applyCursor();
		shape.getCursor()->rotate(5 - Utils::rand(11),0,0,1);
		
		*img << shape;
	}

	return {img};
}
