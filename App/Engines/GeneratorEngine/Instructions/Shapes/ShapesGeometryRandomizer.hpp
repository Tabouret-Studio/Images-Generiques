#ifndef ShapesGeometryRandomizer_hpp
#define ShapesGeometryRandomizer_hpp

#include "../Instruction.hpp"

/*
Instruction de rotation aléatoire des formes pour une VectorImage
*/
class ShapesGeometryRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapesGeometryRandomizer() {};
};

#endif /* ShapesGeometryRandomizer_hpp */
