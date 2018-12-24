#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Util.h"

#include "ECManager.h"

enum ObjectPrimitive
{
	Cube,
	Sphere,
	Plane
};

class Object : public Component
{
public:
	void Init() override;

	int GetVerticesCount();
	int GetIndicesCount();

	void SetActive(bool value);
	bool IsActive();

	void ReloadDefaultTexture();
	void SetNormalMap(std::string normal);

	float* GetVertices();
	unsigned int* GetIndices();

	// Set the default texture
	void SetDefaultTexture(std::string path);
	// Get path to default texture
	std::string GetDefaultTexture();

	// Get file location 
	char* GetFileName();
	// Set file location of the mesh
	void SetFileLocation(char* fileLocation);
	// Set file location of the mesh
	void SetFileLocation(std::string fileLocation);
	// Load model
	// Model is automatically loaded
	NE_ERROR LoadModel();
	// Load model from string
	// Model is NOT automatically loaded
	NE_ERROR LoadModel(const std::string& fileName);
	// Use Primitive as Object
	void UsePrimitive(ObjectPrimitive primitive);
	// Render the model
	// Is called automatically
	void RenderModel();
	// Delete all data on the ram
	void ClearModel();

	~Object();

private:
	// Load single object
	void LoadNode(aiNode *node, const aiScene *scene);
	// Load mesh
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	// Load materials
	void LoadMaterials(const aiScene *scene);

	// Generate vertices, indices & normals
	void PrimitiveCube();
	void PrimitiveSphere();
	void PrimitivePlane();

	// Mesh list
	std::vector<Mesh*> meshList;
	// Texture list
	std::vector<Texture*> textureList;
	// Material index
	std::vector<unsigned int> meshToTex;

	std::vector<float> vertexList;
	std::vector<unsigned int> indexList;

	char* location;

	int indicesCount;
	int verticesCount;

	bool activeModel;
	bool usePrimitive;
	bool drawWireframe;

	std::string defaultPath;

	Texture normal;
};

