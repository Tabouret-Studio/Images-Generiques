//
//  PathsOrderRandomizer.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsOrderRandomizer_hpp
#define PathsOrderRandomizer_hpp

#include "../Instruction.hpp"

class PathsOrderRandomizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:
	PathsOrderRandomizer(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_ORDER, "Reordonner") {};
};

#endif /* PathsOrderRandomizer_hpp */
