//
//  Shader.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Asset.hpp"

#include <iostream>

class Shader : public Asset
{
public:
	Shader(std::string shaderPath, GLenum shaderType);

	/**
	 Set the source stream (char array) for the shader content

	 @param source The sahder content
	 */
	void setSource(const char * source);

	/**
	 Compile the shader in OpenGL
	 Throw an std::runtime_error if the compilation fails
	 */
	void compile();

	/**
	 Return the openGL shader ID

	 @return The shader ID
	 */
	inline GLuint getShaderID() const { return m_shaderID; };

	~Shader();

private:
	
	//Shader infos
	std::string m_shaderPath;
	GLuint m_shaderID;

	const std::string getCompileLog() const;
};

#endif /* Shader_hpp */
