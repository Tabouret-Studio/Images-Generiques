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
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	PathsOrderInvert() {};
};

#endif /* PathsOrderInvert_hpp */
