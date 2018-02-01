#ifndef BeziersHandlesReversing_hpp
#define BeziersHandlesReversing_hpp

#include "../Instruction.hpp"

class BeziersHandlesReversing: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	BeziersHandlesReversing(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"retourner") {};
};

#endif /* BeziersHandlesReversing_hpp */
