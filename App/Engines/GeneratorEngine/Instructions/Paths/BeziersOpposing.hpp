#ifndef BeziersOpposing_hpp
#define BeziersOpposing_hpp

#include "../Instruction.hpp"

class BeziersOpposing: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	BeziersOpposing(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"opposer") {};
};

#endif /* BeziersOpposing_hpp */
