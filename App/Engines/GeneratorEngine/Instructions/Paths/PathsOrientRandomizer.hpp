//
//  PathsOrientRandomizer.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsOrientRandomizer_hpp
#define PathsOrientRandomizer_hpp

#include "../Instruction.hpp"

/*
Instruction de rotation aléatoire des courbes pour une VectorImage
*/
class PathsOrientRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsOrientRandomizer(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"pivoter aléatoirement") {};
};

#endif /* PathsOrientRandomizer_hpp */
