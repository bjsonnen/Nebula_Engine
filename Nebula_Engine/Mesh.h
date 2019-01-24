#pragma once

#include <GL\glew.h>

//! Main class to create a mesh. 
class Mesh
{
public:
	//! Standard Mesh constructor
	Mesh();

	//! Create a mesh based on the vertices and indices
	//! @param vertices Insert vertices as float pointer
	//! @param indecies Insert indices as unsigned int pointer
	//! @param numOfVertices Insert number of all vertices
	//! @param numOfIndices Insert number of all indices
	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	//! Render mesh, called automatically
	//!
	void RenderMesh();
	//! Delete the object
	//! You can simply remove the mesh from meshList. All data is still in ram
	//!
	void ClearMesh();

	//! Returns the Vertex buffer object
	//! @return Returns the VBO as unsigned int
	unsigned int GetVBO();
	//! Returns the Index buffer object
	//! @return Returns the IBO as unsigned int
	unsigned int GetIBO();
	//! Returns the Vertex Array object
	//! @return Returns the VAO as unsigned int
	unsigned int GetVAO();
	//! Returns the size of the vertices
	//! @return Returns the size of the indices as int
	int GetIndices();

	~Mesh();

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
	int indexCount;
};

