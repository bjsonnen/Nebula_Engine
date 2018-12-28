#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"
#include "Util.h"

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

// Primitive Object for testing
enum ObjectPrimitive
{
	Cube,
	Sphere,
	Plane
};

class GameObject
{
public:
	// Create a single model from file
	GameObject();
	// Create a single model from file
	// To load it manually use: LoadModel(std::string)
	GameObject(char* filelocation);

	// Get the current Position
	glm::vec3 GetPosition();
	// Get the current Rotation
	glm::vec3 GetRotation();
	// Get the current Scale
	glm::vec3 GetScale();

	// Get vertice count of each object
	int GetVerticesCount();
	// Get indices count of each object
	int GetIndicesCount();

	// Set the position of the object
	// Position is automatically applied every frame
	void SetPosition(float x, float y, float z);
	// Set the position of the object
	// Position is automatically applied every frame
	void SetPosition(glm::vec3 position);
	// Set the rotation of the object
	// Rotation is automatically applied every frame
	void SetRotation(float x, float y, float z);
	// Set the rotation of the object
	// Rotation is automatically applied every frame
	void SetRotation(glm::vec3 rotation);
	// Set the degree of an object based on the rotatio vector
	// Rotation is automatically applied every frame
	void SetDegrees(float value);
	// Set the scale of the object
	// Scale is automatically applied every frame
	void SetScale(float x, float y, float z);
	// Set the scale of the object
	// Scale is automatically applied every frame
	void SetScale(glm::vec3 scale);

	// Used by the renderer
	// Returns true if the model has bitangents and tangents
	bool GetRenderNormalMaps();

	// Returns the degrees for the axis
	float GetDegrees();

	// Set rotation relative to an object
	void LookAt(glm::vec3 pos);
	// Set rotation relative to an object
	void LookAt(glm::vec2 pos);
	// Set rotation relative to an object
	void LookAt(float x, float y, float z);
	// Show or hide model
	void SetActive(bool value);
	// Return true if model is active
	bool IsActive();
	// Rotate object round value
	void Rotate(glm::vec3 rotation);

	// Load default texture again and delete the old one in ram
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
	void RenderModel();
	// Delete all data on the ram
	void ClearModel();

	~GameObject();

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
	bool useBitangent = true;

	glm::mat4 model = glm::mat4();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rota = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	std::string defaultPath = "Textures/dev.jpg";

	Texture normal;
};

