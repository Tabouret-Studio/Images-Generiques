#ifndef ShapesOrderRandomizer_hpp
#define ShapesOrderRandomizer_hpp

#include "../Instruction.hpp"

class ShapesOrderRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:
	ShapesOrderRandomizer() {};
};

#endif /* ShapesOrderRandomizer_hpp */
