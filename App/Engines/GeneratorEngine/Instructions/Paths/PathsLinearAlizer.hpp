#ifndef PathsLinearAlizer_hpp
#define PathsLinearAlizer_hpp

#include "../Instruction.hpp"

class PathsLinearAlizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages);

private:

	PathsLinearAlizer() {};
};

#endif /* PathsLinearAlizer_hpp */
