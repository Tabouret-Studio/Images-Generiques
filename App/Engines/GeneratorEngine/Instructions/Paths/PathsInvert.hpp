//
//  PathsInvert.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsInvert_hpp
#define PathsInvert_hpp

#include "../Instruction.hpp"

/*
Instruction de bruitage des courbes pour une VectorImage
*/
class PathsInvert: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsInvert(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, "inverser") {};
};

#endif /* PathsInvert_hpp */
