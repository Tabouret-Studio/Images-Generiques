//
//  Vectorizer.hpp
//  Xcode
//
//  Created by Valentin Dufois on 28/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Vectorizer_hpp
#define Vectorizer_hpp

/////////////////////
//Forward declaration
class VectorImage;

#include "libraries.hpp"

#include <boost/process.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <vector>

class Vectorizer
{
public:

	//Convert input image (Convert)
	//Vectorize inpout image (potrace)
	//Save vectorized image somewhere (potrace)
	//Enjoy ?

	Vectorizer();

	Vectorizer(const std::string &inputFile):
		m_inputFile(inputFile) {};

	Vectorizer(const std::string &inputFile, const std::string &outputFile):
		m_inputFile(inputFile),
		m_outputFile(outputFile) {};

	bool vectorize();

	VectorImage * getVectorImage();

private:

	std::string m_inputFile;
	std::string m_transitFile;
	std::string m_outputFile;

	std::vector<boost::filesystem::path> m_searchPaths;

	bool convertInput();
	bool vectorizeInput();
	void clean();
};

#endif /* Vectorizer_hpp */
