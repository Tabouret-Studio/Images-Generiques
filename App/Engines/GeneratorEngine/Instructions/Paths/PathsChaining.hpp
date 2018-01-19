//
//  PathsChaining.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PathsChaining_hpp
#define PathsChaining_hpp

#include "../Instruction.hpp"

class PathsChaining: public Instruction
{
public:

	static Instruction * get();
	
	VectorImage * execute(VectorImage * vectorImage);

private:

	PathsChaining() {};
};

#endif /* PathsChaining_hpp */
