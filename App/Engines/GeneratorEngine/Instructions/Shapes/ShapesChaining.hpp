#ifndef ShapesChaining_hpp
#define ShapesChaining_hpp

#include "../Instruction.hpp"

class ShapesChaining: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapesChaining() {};
};

#endif /* ShapesChaining_hpp */
