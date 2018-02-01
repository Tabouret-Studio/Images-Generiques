#ifndef ShapesOrderInvert_hpp
#define ShapesOrderInvert_hpp

#include "../Instruction.hpp"

/*
Instruction d'inversement de l'ordre des shapes
*/
class ShapesOrderInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapesOrderInvert(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_ORDER, u"inverser") {};
};

#endif /* ShapesOrderInvert_hpp */
