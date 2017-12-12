//
//  NSVG.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 12/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "NSVG.hpp"

namespace Utils
{
	NSVG::NSVG(const std::string &path): m_imagePath(path)
	{
		//Load images
		m_image = ::nsvgParseFromFile(m_imagePath.c_str(), "px", 96);

		float * p;

		//Preload its content -> Store every path of the image as Bezier objects
		for (NSVGshape * shape = m_image->shapes; shape != NULL; shape = shape->next) {
			for (NSVGpath * path = shape->paths; path != NULL; path = path->next) {
				for (int i = 0; i < path->npts-1; i += 3)
				{
					p = &path->pts[i * 2];

					//TODO : Points values adjustements to be updated
					glm::vec2 startP = glm::vec2((p[0] / 500.f) - 1.f, ((p[1] / 375.f) - 1.f) * -1);
					glm::vec2 startH = glm::vec2((p[2] / 500.f) - 1.f, ((p[3] / 375.f) - 1.f) * -1);
					glm::vec2 endH = glm::vec2((p[4] / 500.f) - 1.f, ((p[5] / 375.f) - 1.f) * -1);
					glm::vec2 endP = glm::vec2((p[6] / 500.f) - 1.f, ((p[7] / 375.f) - 1.f) * -1);

					m_paths.push_back(Utils::Bezier(startP, startH, endH, endP));
				}
			}
		}
	}

	std::vector<glm::vec2> NSVG::getAllPoints()
	{
		return getAllPoints(150);
	}

	std::vector<glm::vec2> NSVG::getAllPoints(const uint &precision)
	{
		std::vector<glm::vec2> vertices, pathVertices;

		// Parse SVG
		for(std::vector<Utils::Bezier>::iterator it = m_paths.begin(); it != m_paths.end(); ++it)
		{
			pathVertices = (*it).getPoints(precision);

			vertices.insert(vertices.end(), pathVertices.begin(), pathVertices.end());
		}

		return vertices;
	}
}
