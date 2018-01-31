//
//  libraries.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 30/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef libraries_h
#define libraries_h

///////////////////
// Needed libraries

//GL + GLEW
#include <GL/glew.h>

//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//SDL2 Image
#ifdef __APPLE__
#    include <SDL2_image/SDL_image.h>
#else
#    include <SDL2/SDL_image.h>
#endif

//FreeType 2
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_GLYPH_H

//Assimp
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

//GLM
#define GLM_SWIZZLE_RGBA
#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

//////////
//NanoSVG
#include <NanoSVG/nanosvg.h>

//////////
//JSON
#include "JSON/json.hpp"

/////////////////
//UUID generation
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

//PYTHON INSTRUCTION
//#define IG_PYTHON_INSTRUCTIONS


//////////////////
//OpenGL Debugging
void _check_gl_error(const char *file, int line);
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)
//////////////////


//////////
//Typedefs
using rId = boost::uuids::uuid;
using srcId = boost::uuids::uuid;

#endif /* libraries_h */
