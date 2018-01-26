#ifndef BeziersOpposing_hpp
#define BeziersOpposing_hpp

#include "../Instruction.hpp"

class BeziersOpposing: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages);

private:

	BeziersOpposing() {};
};

#endif /* BeziersOpposing_hpp */
