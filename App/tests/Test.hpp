//
//  Test.h
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Test_h
#define Test_h

namespace Tests
{
	class Test
	{
	public:
		/**
		 Called only one time at program start
		 */
		virtual void setup() = 0;

		/**
		 Called every frame
		 */
		virtual void render() = 0;
	private:
	};
}

//Include all tests hpp files here
#include "whiteTriangle.hpp"
#include "Val01.hpp"

#endif /* Test_h */
