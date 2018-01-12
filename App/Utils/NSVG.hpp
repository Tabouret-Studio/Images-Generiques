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
		/**
		 Open and parse a SVG image using the NanoSVG library
		 */
		NSVG(const std::string &path);
		~NSVG();

		/**
		 Get all the paths of the image as Bezier objects

		 @return Vector of Bezier curves
		 */
		inline std::vector<Bezier> getAllPaths() const { return m_paths; };

		/**
		 Return all points on the image, including curves, with a precision of 150

		 @return Vector of vec2
		 */
		std::vector<glm::vec2> getAllPoints();
		/**
		 Return all points on the image, including curves

		 @param precision Number of points per curve
		 @return Vector of vec2
		 */
		std::vector<glm::vec2> getAllPoints(const uint &precision);

	private:
		std::string m_imagePath;

		//NSVG ELEMENTS
		NSVGimage * m_image;

		std::vector<Bezier> m_paths;
	};
}

#endif /* NSVG_hpp */
