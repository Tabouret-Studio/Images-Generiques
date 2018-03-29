//
//  Utils.hpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <vector>

namespace Utils
{
	int rand(int i);

	/**
	 Return the nth point on the interval.

	 - coef values: 0 = starting point, 1 = end point

	 @param A The starting point
	 @param B The end point
	 @param coef Point to return in percentage
	 @return The value of the point
	 */
	template<typename T>
	T getIPointBetween(const T &A, const T &B, const float &coef)
	{
		return A + ((B - A) * coef);
	}

	std::vector<std::string> decomposeByDelimiter(std::string s, const std::string &delimiter);
}

#endif /* Utils_hpp */
