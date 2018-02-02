//
//  InstructionParameters.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "InstructionParameters.hpp"

void InstructionParameters::createParam(const std::string &paramName, const float &paramValue)
{
	if(hasParam(paramName))
		m_parameters[paramName] = paramValue;

	m_parameters.insert(std::pair<std::string, float>(paramName, paramValue));
}

void InstructionParameters::updateParam(const std::string &paramName, const float &paramValue)
{
	if(!hasParam(paramName))
		throw std::runtime_error("Could not update parameters.\nThe parameter \""+paramName+"\" does not exist.");

	m_parameters[paramName] = paramValue;
}

bool InstructionParameters::hasParam(const std::string &paramName)
{
	if(m_parameters.find(paramName) != m_parameters.end())
		return true;

	return false;
}

float InstructionParameters::getParam(const std::string &paramName)
{
	if(!hasParam(paramName))
		throw std::runtime_error("Could not get parameter.\nThe parameter \""+paramName+"\" does not exist.");

	return m_parameters[paramName];
}

void InstructionParameters::removeParam(const std::string &paramName)
{
	if(!hasParam(paramName))
		throw std::runtime_error("Could not remove parameter.\nThe parameter \""+paramName+"\" does not exist.");

	m_parameters.erase(paramName);
}
