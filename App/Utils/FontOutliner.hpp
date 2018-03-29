//
//  FontOutliner.hpp
//  Xcode
//
//  Created by Valentin Dufois on 28/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef FontOutliner_hpp
#define FontOutliner_hpp

#include "libraries.hpp"
#include "Elements/Vector/Shape.hpp"

struct FontOutliner
{
	glm::vec3 m_lastPoint;
	Shape m_letterShape;

	static int MoveToFunction(const FT_Vector *to, void *user);
	static int LineToFunction(const FT_Vector *to, void *user);
	static int ConicToFunction(const FT_Vector *control, const FT_Vector *to, void *user);
	static int CubicToFunction(const FT_Vector *controlOne, const FT_Vector *controlTwo, const FT_Vector *to, void *user);
};

#endif /* FontOutliner_hpp */
