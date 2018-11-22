#pragma once

#include <GL\glew.h>

class Mesh
{
public:
	Mesh();

	// Create a mesh based on the vertices and indices
	void CreateMesh(float *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	// Render mesh, called automatically
	void RenderMesh();
	// Delete the object
	// You can simply remove the mesh from meshList. All data is still in ram
	void ClearMesh();

	// Returns the Vertex buffer object
	unsigned int GetVBO();
	// Returns the Index buffer object
	unsigned int GetIBO();
	// Returns the Vertex Array object
	unsigned int GetVAO();
	// Returns the size of the vertices
	int GetIndices();

	~Mesh();

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
	int indexCount;
};

