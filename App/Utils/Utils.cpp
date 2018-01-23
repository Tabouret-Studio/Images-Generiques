//
//  Utils.cpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Utils.hpp"

#include <cstdlib>

namespace Utils
{
	int rand(int i)
	{
		return std::rand() % i;
	}

}
