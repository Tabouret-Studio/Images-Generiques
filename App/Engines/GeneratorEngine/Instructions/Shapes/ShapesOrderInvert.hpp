#ifndef ShapesOrderInvert_hpp
#define ShapesOrderInvert_hpp

#include "../Instruction.hpp"

/*
Instruction d'inversement de l'ordre des shapes
*/
class ShapesOrderInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapesOrderInvert() {};
};

#endif /* ShapesOrderInvert_hpp */
