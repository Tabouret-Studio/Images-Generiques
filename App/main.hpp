//
//  main.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef main_h
#define main_h

#define FRAMERATE 30

//SET TEST CLASSNAME HERE
#define TESTCLASS Val01

//System includes
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <stdio.h>
#include <string.h>
#include <math.h>

//OpenGL and friends
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

//SVG files (NanoSVG)
#define NANOSVG_ALL_COLOR_KEYWORDS
#include <NanoSVG/nanosvg.h>

//App core
#include "Core/AppObject.hpp"
#include "Core/Core.hpp"

//App Engines
#include "Engines/AppEngine/AppEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

//Utils
#include "Utils/vertexColor.h"
#include "Utils/Bezier.hpp"
#include "Utils/NSVG.hpp"

//Tests
#include "tests/Test.hpp"

#endif /* main_h */
