#ifndef ShapesGeometryRandomizer_hpp
#define ShapesGeometryRandomizer_hpp

#include "../Instruction.hpp"

/*
Instruction de rotation aléatoire des formes pour une VectorImage
*/
class ShapesGeometryRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapesGeometryRandomizer(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_GEOMETRY, u"pivoter aléatoirement") {};
};

#endif /* ShapesGeometryRandomizer_hpp */
