#ifndef ShapesGeometryInvert_hpp
#define ShapesGeometryInvert_hpp

#include "../Instruction.hpp"

/*
Instruction d'inversement de l'ordre des shapes
*/
class ShapesGeometryInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapesGeometryInvert() {};
};

#endif /* ShapesGeometryInvert_hpp */
