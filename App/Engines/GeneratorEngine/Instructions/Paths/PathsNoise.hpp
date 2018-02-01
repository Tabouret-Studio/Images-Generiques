//
//  PathsNoise.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsNoise_hpp
#define PathsNoise_hpp

#include "../Instruction.hpp"

/*
Instruction de bruitage des courbes pour une VectorImage
*/
class PathsNoise: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsNoise(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"translater aléatoirement") {};
};

#endif /* PathsNoise_hpp */
