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

class Object : public Component
{
public:
	// Create a single model from file
	Object();
	// Create a single model from file
	// To load it manually use: LoadModel(std::string)
	Object(char* filelocation);

	void Init() override;
	void Update() override;

	// Primitive Object for testing
	enum ObjectPrimitive
	{
		Cube,
		Sphere,
		Plane
	};

	// Get vertice count of each object
	int GetVerticesCount();
	// Get indices count of each object
	int GetIndicesCount();

	void ReloadDefaultTexture();

	// Set normal map for mesh
	void SetNormalMap(std::string normal);

	// Returns a pointer to an array with all vertices
	float* GetVertices();
	// Returns a pointer to an array with all indices
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
	NE_ERROR RenderModel();
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

	int indicesCount = 0;
	int verticesCount = 0;

	float rotaDegrees = 0.0f;

	bool activeModel = true;
	bool usePrimitive = false;
	bool drawWireframe = false;

	glm::mat4 model = glm::mat4();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rota = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	std::string defaultPath = "Textures/dev.jpg";

	Texture normal;
};

