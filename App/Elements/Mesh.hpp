//
//  Mesh.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

/////////////////////
//Forward declaration
class ShaderProgram;

#include "Asset.hpp"
#include "Utils/DrawCursor.hpp"
#include "Utils/Vertex.hpp"

class Mesh : public Asset
{
public:
	//Constructor
	Mesh();
	Mesh(const std::vector<Vertex> vertexList);

	//Getters
	/**
	 Return all vertex in the mesh
	 @return An array of vertex
	 */
	inline std::vector<Vertex> getVertexList() const { return m_vertexList; };

	/**
	 Return the number of vertex in the mesh
	 Shortcut for *getVertexList().size()*

	 @return Number of vertex
	 */
	unsigned long getVertexCount() const { return m_vertexList.size(); }

	/**
	 Return the texture ID used by the mesh

	 @return Texture ID
	 */
	GLuint getTextureID() const { return m_textureID; }

	/**
	 Return the program ID (Shaders) used by the mesh

	 @return Program ID
	 */
	ShaderProgram * getProgram() const { return m_program; }

	/**
	 Tell if the mesh is textured

	 @return True if textured, false otherwise
	 */
	inline bool isTextured() const { return m_textureID != 0; };

	/**
	 Get the min boundaries of the mesh

	 @return XYZ coordinates
	 */
	inline glm::vec3 getBoundariesMin() const { return m_boundsMin; };

	/**
	 Get the max boundaries of the mesh

	 @return XYZ coordinates
	 */
	inline glm::vec3 getBoundariesMax() const { return m_boundsMax; };

	/**
	 Return the dimensions of the mesh

	 @return XYZ dimensions
	 */
	glm::vec3 getDimensions() const;
	 

	//Utils
	/**
	 Fill the mesh vertex with the given ones
	 Replace existing vertex

	 @param vertexList A vector of Vertex
	 */
	void fillVertex(const std::vector<Vertex> &vertexList);

	/**
	 Set the texture ID for the mesh
	 the texture will not be freeed on deletion of the mesh

	 @param textureID The texture ID
	 */
	inline void setTexture(const GLuint &textureID) { setTexture(textureID, false); };

	/**
	 Set the texture ID for the mesh
	 Tell if the texture needs to be freeed at the same time as the mesh

	 @param textureID The texture ID
	 */
	void setTexture(const GLuint &textureID, const bool &toFree);

	/**
	 Set the Program ID for the mesh

	 @param program The program ID
	 */
	inline void setProgram(ShaderProgram * program) { m_program = program; };

	/**
	 Generate OpenGL buffers for the mesh
	 */
	void generate();

	inline bool isGenerated() const { return m_generated; };

	/**
	 Get a pointer to the mesh VBO ID

	 @return Pointer to the vbo
	 */
	inline GLuint * getVBO() { return &m_vbo; };
	inline const GLuint * getVBO() const { return &m_vbo; };

	/**
	 Get a pointer to the mesh VAO ID

	 @return Pointer to the vao
	 */
	inline GLuint * getVAO() { return &m_vao; };
	inline const GLuint * getVAO() const { return &m_vao; };

	/**
	 Return the drawing cursor of the object

	 @return The cursor
	 */
	inline DrawCursor * getCursor() { return &m_cursor; };

	/**
	 Apply the cursor matrix to the mesh vertex
	 then reset cursor
	 */
	void applyCursor();

	/**
	 Set the render format used by OpenGL to render this mesh
	 Default format : GL_TRIANGLES

	 @param format New format (GL_LINES, GL_TRIANGLES, GL_POINTS, etc.)
	 */
	inline void setRenderFormat(const GLenum &format) { m_renderFormat = format; };

	/**
	 Tell the OpenGL render format used by this mesh
	 Default format : GL_TRIANGLES

	 @return The format (GL_LINES, GL_TRIANGLES, GL_POINTS, etc.)
	 */
	inline GLenum getRenderFormat() const { return m_renderFormat; };

	/**
	 Set the color for all the vertex in the mesh
	 Mainly used to render text
	 */
	void setColor(const glm::vec4 &color);

	/**
	 Tell the point size for this mesh

	 @return The point size
	 */
	inline uint getPointSize() const { return m_pointSize; };

	/**
	 Set the point size for this mesh

	 @param pointSize the point size
	 */
	inline void setPointSize(const uint &pointSize) { m_pointSize = pointSize; };

	/**
	 Shortcut to render the mesh with its own cursor
	 */
	void render() const;

	///////////
	//Operators

	/**
	 Append new vertex to the existing ones

	 @param vertexList A vector of vertex
	 */
	Mesh &operator <<(const std::vector<Vertex> &vertexList);

	/**
	 Append a new vertex to the existing one

	 @param vertex A vertex
	 */
	Mesh &operator <<(const Vertex &vertex);

	/**
	 Append a new vertex to the existing one

	 @param mesh A vertex
	 */
	Mesh &operator <<(const Mesh * mesh);

	/////////////
	//Destructors

	/**
	 Liberate the texture used by the mesh
	 */
	void freeTexture();

	~Mesh();

private:
	//Vertex
	std::vector<Vertex> m_vertexList;

	GLuint m_vbo;
	GLuint m_vao;
	bool m_generated;

	glm::vec3 m_boundsMin;
	glm::vec3 m_boundsMax;

	/**
	 Calculate mesh boundaries
	 */
	void calculateBoundaries();

	/**
	 Update Mesh boundaries with given vertex

	 @param newVertex Vertex to update boundaries with
	 */
	void updateBoundaries(const std::vector<Vertex> &newVertex);

	//Position
	DrawCursor m_cursor;

	//Texture
	GLuint m_textureID;
	bool m_freeTexture;
	
	//Shader program
	ShaderProgram * m_program = nullptr;

	//Render type
	GLenum m_renderFormat;
	uint m_pointSize = 1;

	void deleteBuffers();
};

#endif /* Mesh_hpp */
