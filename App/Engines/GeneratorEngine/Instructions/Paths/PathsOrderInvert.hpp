#ifndef PathsOrderInvert_hpp
#define PathsOrderInvert_hpp

#include "../Instruction.hpp"

/*
Instruction d'inversement de l'ordre des béziers
*/
class PathsOrderInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsOrderInvert(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_ORDER, u"renverser") {};
};

#endif /* PathsOrderInvert_hpp */
