//
//  NSVG.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef NSVG_hpp
#define NSVG_hpp

#define NANOSVG_IMPLEMENTATION
#include "../main.hpp"

namespace Utils {
	class NSVG
	{
	public:
		NSVG(const std::string &path);

		inline std::vector<Bezier> getAllPaths() const { return m_paths; };

		std::vector<glm::vec2> getAllPoints();
		std::vector<glm::vec2> getAllPoints(const uint &precision);

	private:
		std::string m_imagePath;

		//NSVG ELEMENTS
		NSVGimage * m_image;

		std::vector<Bezier> m_paths;
	};
}

#endif /* NSVG_hpp */
