//
//  RenderEngine.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 19/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef RenderEngine_hpp
#define RenderEngine_hpp

#define GL_DEFAULT_CLEAR_COLOR glm::vec4(1.0, 1.0, 1.0, 1.0)

//////////////////////
//Forward declarations
class Mesh;

//Get engine dependancies
#include "libraries.hpp"
#include "Utils/DrawCursor.hpp"

/**
 All major OpenGL interactions are holds here
 Allow for easy interactions with OpenGL
 */
class RenderEngine
{
public:
	//Singleton
	static void instanciate();


	/**
	 Init render properties such as matrix
	 */
	void initRender();

	///////////
	//Rendering

	/**
	 Set up the projection Matrix for 3D render
	 */
	void setProjection3D();

	/**
	 Fast forward call to setProjection2D with window dimensions
	 */
	void setProjection2D();
	
	/**
	 Set up the projection matrix for 2D render

	 @param width Width in px of the screen
	 @param height Height in px of the screen
	 */
	void setProjection2D(const float &width, const float &height);

	/**
	 Return the cursor of the camera.
	 Allow for camera manipulation

	 @return The camera cursor
	 */
	inline DrawCursor * getCameraCursor() { return &m_MVMatrix; };

	//////////////////////
	//OpenGL Manipulations

	void setClearColor(const glm::vec4 &clearColor);

	inline glm::vec4 getClearColor() const { return m_clearColor; };

	///////
	//Utils

	/**
	 Generate the VBO for the given mesh

	 @param mesh Mesh to generate
	 */
	void initVBO(Mesh * mesh);

	/**
	 Generate the VAO for the given mesh

	 @param mesh Mesh to generate
	 */
	void initVAO(Mesh * mesh);

	/**
	 Render the given mesh at the given location

	 @param mesh The mesh to render
	 @param cursor Cursor to the mesh position
	 */
	void render(const Mesh * mesh, const DrawCursor * cursor);

private:

	//Singleton
	static bool m_instanciated;

	//Vertice Properties
	const GLuint VERTEX_ATTR_POSITION = 1;
	const GLuint VERTEX_ATTR_NORMAL = 2;
	const GLuint VERTEX_ATTR_COLOR = 3;
	const GLuint VERTEX_ATTR_UV = 4;

	//Cameras
	bool thirdPersCamera = false;

	//Matrix
	DrawCursor m_ProjectionMatrix;
	DrawCursor m_MVMatrix;
	DrawCursor m_NormalMatrix;

	DrawCursor m_storedMVMatrix;
	bool m_stored;

	//OpenGL properties
	glm::vec4 m_clearColor;

	//Constructor
	RenderEngine();
	~RenderEngine();
};

#endif /* RenderEngine_hpp */
