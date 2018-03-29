#ifndef BeziersAmplitude_hpp
#define BeziersAmplitude_hpp

#include "../Instruction.hpp"

class BeziersAmplitude: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	BeziersAmplitude(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"amplifier") {};
};

#endif /* BeziersAmplitude_hpp */
