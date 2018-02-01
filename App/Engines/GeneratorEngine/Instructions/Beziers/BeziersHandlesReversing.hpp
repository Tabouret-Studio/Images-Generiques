#ifndef BeziersHandlesReversing_hpp
#define BeziersHandlesReversing_hpp

#include "../Instruction.hpp"

class BeziersHandlesReversing: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	BeziersHandlesReversing() {};
};

#endif /* BeziersHandlesReversing_hpp */
