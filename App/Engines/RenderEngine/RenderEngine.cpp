//
//  RenderEngine.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 19/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "RenderEngine.hpp"

#include "Utils/Vertex.hpp"
#include "Utils/SDL.hpp"
#include "Utils/ShaderProgram.hpp"
#include "Core/AppObject.hpp"
#include "Elements/Mesh.hpp"

bool RenderEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void RenderEngine::instanciate()
{
	if(m_instanciated)
		return;

	App->renderEngine = new RenderEngine();

	m_instanciated = true;
}

/**
 * Private constructor
 */
RenderEngine::RenderEngine():
	m_stored(false),
	m_clearColor(GL_DEFAULT_CLEAR_COLOR) {}

void RenderEngine::initRender()
{
	////////////////////
	//Set OpenGL options
	setClearColor(GL_DEFAULT_CLEAR_COLOR);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(1);

	glEnable(GL_MULTISAMPLE_ARB);

	/////////////
	//Set matrixs

	//MV Matrix <- The camera in a sort
	m_MVMatrix.setMatrix(glm::mat4(1.0));

	//Normals
	m_NormalMatrix = m_MVMatrix;
	m_NormalMatrix.inverse()->transpose();

	setProjection3D();
}

void RenderEngine::setProjection3D()
{
	float screenRatio = (float) App->getWidth() / App->getHeight();

	m_ProjectionMatrix.setMatrix(glm::mat4(1.0))
		->perspective(70.f, screenRatio, 0.1f, 1500.f);

	glViewport(0, 0, App->getWidth(), App->getHeight());

	if(m_stored)
	{
		m_stored = false;
		m_MVMatrix = m_storedMVMatrix;
	}
}

void RenderEngine::setProjection2D()
{
	setProjection2D(App->getWidth(), App->getHeight());
}

void RenderEngine::setProjection2D(const float &width, const float &height)
{
	m_ProjectionMatrix.setMatrix(glm::ortho(0.f, width, height, 0.f));

	glViewport(0, 0, width, height);

	m_storedMVMatrix = m_MVMatrix;
	m_MVMatrix.setMatrix(glm::mat4(1.0));
	m_stored = true;
}

void RenderEngine::setClearColor(const glm::vec4 &clearColor)
{
	m_clearColor = clearColor;
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
}

void RenderEngine::initVBO(Mesh * mesh)
{
	//Get Manager for VBO

	//Generate & bind VBO
	glGenBuffers(1, mesh->getVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *mesh->getVBO());

	//Fill VBO with data
	std::vector<Vertex> vertexList = mesh->getVertexList();

	GLsizeiptr size = vertexList.size() * sizeof(Vertex);

	//Fill VBO with data
	glBufferData(
				 GL_ARRAY_BUFFER,
				 size,
				 vertexList.data(),
				 GL_STATIC_DRAW
				 );

	//Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderEngine::initVAO(Mesh * mesh)
{
	if(*mesh->getVBO() == 0)
		return; //No VBO, No VAO!

	glGenVertexArrays(1, mesh->getVAO());
	glBindVertexArray(*mesh->getVAO());

	//Bind mesh VBO
	glBindBuffer(GL_ARRAY_BUFFER, *mesh->getVBO());

	//Vertex attribs
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
	glEnableVertexAttribArray(VERTEX_ATTR_UV);

	//Specify vertice properties positions
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, normal));
	glVertexAttribPointer(VERTEX_ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, color));
	glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)offsetof(Vertex, UV));

	//Unbind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RenderEngine::render(const Mesh * mesh, const DrawCursor * cursor)
{
	if(*mesh->getVAO() == 0)
		return; //No VAO, no render!

	//Set program
	mesh->getProgram()->use();

	//Bind texture if needed
	if(mesh->isTextured())
	{
		glBindTexture(GL_TEXTURE_2D, mesh->getTextureID());
		check_gl_error();
		mesh->getProgram()->setUniformUint("uTexturedMesh", 1);
		mesh->getProgram()->setUniformUint("uTexture", 0);
	}
	else
	{
		mesh->getProgram()->setUniformUint("uTexturedMesh", 0);
	}

	//Send uniforms to GPU
	mesh->getProgram()->setUniformMat4("uMVMatrix", m_MVMatrix);
	mesh->getProgram()->setUniformMat4("uNormalMatrix", m_NormalMatrix);
	mesh->getProgram()->setUniformMat4("uMVPMatrix", m_ProjectionMatrix * m_MVMatrix * cursor->getMatrix());

	//Bind VAO
	glBindVertexArray(*mesh->getVAO());

	if(mesh->getRenderFormat() == GL_POINTS)
		glPointSize(mesh->getPointSize());

	//Draw cube
	glDrawArrays(mesh->getRenderFormat(), 0, (GLsizei)mesh->getVertexCount());
	check_gl_error();

	//Debind and clean
	if(mesh->isTextured())
		glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}
