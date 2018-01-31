//
//  ShapeIndex.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ShapeIndex_hpp
#define ShapeIndex_hpp

#include "../Instruction.hpp"

class ShapeIndex: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapeIndex() {};
};

#endif /* ShapeIndex_hpp */
