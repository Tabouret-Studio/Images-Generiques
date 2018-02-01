#ifndef ShapesOrderRandomizer_hpp
#define ShapesOrderRandomizer_hpp

#include "../Instruction.hpp"

class ShapesOrderRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:
	ShapesOrderRandomizer(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_ORDER, u"réordonner") {};
};

#endif /* ShapesOrderRandomizer_hpp */
