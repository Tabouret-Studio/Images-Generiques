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
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	PathsIndex() {};
};

#endif /* PathsIndex_hpp */
