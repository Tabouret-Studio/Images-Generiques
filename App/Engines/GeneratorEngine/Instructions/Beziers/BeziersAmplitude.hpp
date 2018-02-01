#ifndef BeziersAmplitude_hpp
#define BeziersAmplitude_hpp

#include "../Instruction.hpp"

class BeziersAmplitude: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	BeziersAmplitude() {};
};

#endif /* BeziersAmplitude_hpp */
