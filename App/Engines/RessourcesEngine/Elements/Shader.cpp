//
//  Shader.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Shader.hpp"

#include "libraries.hpp"

Shader::Shader(std::string shaderPath, GLenum shaderType):
	Asset(SHADER),
	m_shaderPath(shaderPath),
	m_shaderID(glCreateShader(shaderType)) {};

void Shader::setSource(const char * source)
{
	glShaderSource(m_shaderID, 1, &source, 0);
}

void Shader::compile()
{
	glCompileShader(m_shaderID);

	GLint status;
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &status);

	if(status == GL_TRUE)
		return;

	throw std::runtime_error("Unable to compile shader " + m_shaderPath + " : " + getCompileLog());
}

const std::string Shader::getCompileLog() const
{
	GLint length;
	glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];

	glGetShaderInfoLog(m_shaderID, length, 0, log);

	std::string logString(log);
	delete [] log;

	return logString;
}

Shader::~Shader()
{
	glDeleteShader(m_shaderID);
}
