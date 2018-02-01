#ifndef ShapesGeometryInvert_hpp
#define ShapesGeometryInvert_hpp

#include "../Instruction.hpp"

/*
Instruction d'inversement de l'ordre des shapes
*/
class ShapesGeometryInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapesGeometryInvert(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_GEOMETRY, u"inverser") {};
};

#endif /* ShapesGeometryInvert_hpp */
