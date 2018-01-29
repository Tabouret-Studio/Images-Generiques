//
//  Vectorizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 28/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Vectorizer.hpp"

#include "Core/AppObject.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include <cstdio>

bool Vectorizer::vectorize()
{
	if(m_outputFile.length() == 0)
		m_outputFile = m_inputFile.substr(0, m_inputFile.find_last_of('.')) + ".svg";

	m_transitFile = m_inputFile.substr(0, m_inputFile.find_last_of('.')) + ".pnm";

	//Store PATH
	m_searchPaths = boost::this_process::path();

#ifdef __APPLE__
	//Add /usr/local/bin to local PATH on macOs
	m_searchPaths.push_back("/usr/local/bin");
#endif

	//Convert to transit format
	convertInput();

	//Vectorize transit to output
	vectorizeInput();

	clean();

	return true;
}

bool Vectorizer::convertInput()
{
	//Get executable
	boost::filesystem::path process = boost::process::search_path("convert", m_searchPaths);

	//Launch
	boost::process::system(process, App->getAppPath() + m_inputFile, App->getAppPath() + m_transitFile);

	return true;
}

bool Vectorizer::vectorizeInput()
{
	//Get executable
	boost::filesystem::path process = boost::process::search_path("potrace", m_searchPaths);

	//Launch
	boost::process::system(process, App->getAppPath() + m_transitFile, "-o", App->getAppPath() + m_outputFile, "--svg");

	return true;
}

void Vectorizer::clean()
{
	std::remove(m_transitFile.c_str());
}
