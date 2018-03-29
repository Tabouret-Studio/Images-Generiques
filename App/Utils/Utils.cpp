//
//  Utils.cpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Utils.hpp"

#include <cstdlib>
#include <ctime>

namespace Utils
{
	int rand(int i)
	{
		//std::srand(unsigned(std::time(0)));
		return std::rand() % i;
	}

	std::vector<std::string> decomposeByDelimiter(std::string s, const std::string &delimiter)
	{
		size_t pos = 0;
		std::string token;
		std::vector<std::string> elements;

		while((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			elements.push_back(token);
			s.erase(0, pos + delimiter.length());
		}

		elements.push_back(s);

		return elements;
	}
}
