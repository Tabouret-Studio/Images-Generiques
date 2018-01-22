//
//  MeshGroup.hpp
//  Xcode
//
//  Created by Valentin Dufois on 18/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef MeshGroup_hpp
#define MeshGroup_hpp

//Forward declarations
class Mesh;

#include "DrawCursor.hpp"

#include <vector>

/**
 Group of mesh for easier manipulation.
 Provide a unfied Render method for easier rendering and lighter code
 as well as Cursor for whole group transformation.
 */
class MeshGroup
{
public:

	//////////////
	//Constructors

	MeshGroup() {};
	MeshGroup(Mesh * mesh):
		m_meshs(std::vector<Mesh *>{mesh}) {};
	MeshGroup(std::vector<Mesh *> meshs):
	m_meshs(meshs) {};

	/**
	 Return all the meshs in the group

	 @return std::vector with mesh pointers
	 */
	std::vector<Mesh *> getMeshs() { return m_meshs; };

	/**
	 Render all the mesh in the group
	 */
	void render();

	/**
	 Get the cursor of the group

	 @return Draw cursor pointer
	 */
	inline DrawCursor * getCursor() { return &m_cursor; };

	/**
	 Append the given mesh at the end of the group

	 @param mesh The mesh to add
	 */
	MeshGroup &operator <<(Mesh * mesh);

	/**
	 Append the given vector of mesh at the end of the group

	 @param meshs The vector to append
	 */
	MeshGroup &operator <<(std::vector<Mesh *> meshs);

	~MeshGroup();

private:

	std::vector<Mesh *> m_meshs;

	DrawCursor m_cursor;

};

#endif /* MeshGroup_hpp */
