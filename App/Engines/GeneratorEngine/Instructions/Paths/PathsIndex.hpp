//
//  PathsIndex.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsIndex_hpp
#define PathsIndex_hpp

#include "../Instruction.hpp"

class PathsIndex: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsIndex(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"indexer") {};
};

#endif /* PathsIndex_hpp */
