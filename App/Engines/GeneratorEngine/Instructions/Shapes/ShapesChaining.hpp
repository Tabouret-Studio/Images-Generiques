#ifndef ShapesChaining_hpp
#define ShapesChaining_hpp

#include "../Instruction.hpp"

class ShapesChaining: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapesChaining(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_ORDER, u"chainer") {};
};

#endif /* ShapesChaining_hpp */
