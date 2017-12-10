//
//  main.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "main.hpp"

int main(int argc, char * argv[])
{
    //The App
	Core core;

	core.ignite();

	App->setAppPath(argv[0]);

	core.main();

	return 0;
}
