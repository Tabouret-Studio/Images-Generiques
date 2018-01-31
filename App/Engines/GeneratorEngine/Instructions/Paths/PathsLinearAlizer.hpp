#ifndef PathsLinearAlizer_hpp
#define PathsLinearAlizer_hpp

#include "../Instruction.hpp"

class PathsLinearAlizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	PathsLinearAlizer(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, "Linearisation") {};
};

#endif /* PathsLinearAlizer_hpp */
