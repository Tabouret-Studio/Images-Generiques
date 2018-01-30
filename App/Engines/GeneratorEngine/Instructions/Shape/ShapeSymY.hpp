//
//  ShapeSymY.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ShapeSymY_hpp
#define ShapeSymY_hpp

#include "../Instruction.hpp"

/*
Instruction de bruitage des courbes pour une VectorImage
*/
class ShapeSymY: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	ShapeSymY() {};
};

#endif /* ShapeSymY_hpp */
