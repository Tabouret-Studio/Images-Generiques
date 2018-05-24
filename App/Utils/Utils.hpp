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
	/**
	 Return a random int using the given parameter as a seed

	 @param i The seed
	 @return Random (Semi random because nothing is truly random) number
	 */
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

	/**
	 String.split(del) method
	 Split a string by a delimiter and return an array of string

	 @param s The full string
	 @param delimiter The delimiter
	 @return Array of strings
	 */
	std::vector<std::string> decomposeByDelimiter(std::string s, const std::string &delimiter);
}

#endif /* Utils_hpp */
