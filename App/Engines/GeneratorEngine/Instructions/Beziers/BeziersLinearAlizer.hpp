#ifndef BeziersLinearAlizer_hpp
#define BeziersLinearAlizer_hpp

#include "../Instruction.hpp"

class BeziersLinearAlizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	BeziersLinearAlizer() {};
};

#endif /* BeziersLinearAlizer_hpp */
