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

//! Primitive object for testing
//!
enum ObjectPrimitive
{
	Cube,
	Sphere,
	Plane
};

//! Primitive object color
//!
enum ObjectColor
{
	Red,
	Blue,
	Green,
	Gray,
	Purple,
	Yellow,
	Orange,
	Black,
	White
};

//! Main class for all gameobjects
class GameObject
{
public:
	//! Create a single model from file
	//! Only reserves the space on the ram
	GameObject();

	//! Create a single model from file
	//! @param fileLocation Insert file location
	//! @see GameObject::LoadModel(std::string)
	GameObject(char* filelocation);

	//! Get the current Position
	//! @return Returns the position of the object as glm::vec3
	glm::vec3 GetPosition();
	//! Get the current Position
	//! @return Returns the position of the object as Vector3
	Vector3 GetPositionVector3();
	//! Get the current Rotation
	//! @return Returns the rotation of the object as glm::vec3
	glm::vec3 GetRotation();
	//! Get the current Rotation
	//! @return Returns the rotation of the object as Vector3
	Vector3 GetRotationVector3();
	//! Get the current Scale
	//! @return Returns the scale of the object as glm::vec3
	glm::vec3 GetScale();
	//! Get the current Scale
	//! @return Returns the scale of the object as Vector3
	Vector3 GetScaleVector3();

	//! Get vertice count of each object
	//! @return Returns the vertices count as int
	int GetVerticesCount();
	//! Get indices count of each object
	//! @return Returns the indices count as int
	int GetIndicesCount();

	//! Set the position of the object
	//! Position is automatically applied every frame
	//! @param x Insert x position
	//! @param y Insert y position
	//! @param z Insert z position
	void SetPosition(float x, float y, float z);

	//! Set the position of the object
	//! Position is automatically applied every frame
	//! @param position Insert the position as glm::vec3
	void SetPosition(glm::vec3 position);
	//! Set the position of the object
	//! Position is automatically applied every frame
	//! @param position Insert the position as Vector3
	void SetPosition(Vector3 position);

	//! Set the rotation of the object
	//! Rotation is automatically applied every frame
	//! @param x Insert x position
	//! @param y Insert y position
	//! @param z Insert z position
	void SetRotation(float x, float y, float z);

	//! Set the rotation of the object
	//! Rotation is automatically applied every frame
	//! @param rotation Insert the rotation as glm::vec3
	void SetRotation(glm::vec3 rotation);
	//! Set the rotation of the object
	//! Rotation is automatically applied every frame
	//! @param rotation Insert the rotation as Vector3
	void SetRotation(Vector3 rotation);

	//! Set the degree of an object based on the rotation vector
	//! Rotation is automatically applied every frame
	//! @param value Insert degrees as flaot
	void SetDegrees(float value);

	//! Set the scale of the object
	//! Scale is automatically applied every frame
	//! @param x Insert x position
	//! @param y Insert y position
	//! @param z Insert z position
	void SetScale(float x, float y, float z);

	//! Set the scale of the object
	//! Scale is automatically applied every frame
	//! @param scale Insert the scale as glm::vec3
	void SetScale(glm::vec3 scale);
	//! Set the scale of the object
	//! Scale is automatically applied every frame
	//! @param scale Insert the scale as Vector3
	void SetScale(Vector3 scale);

	//! Used by the renderer
	//! Returns true if the model has bitangents and tangents
	//! @return Returns if the object has normal maps as bool
	bool GetRenderNormalMaps();

	//! Change the normal map of an object
	//! Do not forget to call ReloadDefaultTexture()
	//! @param location Insert file location as char array
	void SetNormalMap(char* location);

	//! Returns the degrees for the axis
	//! @return Returns the current degrees as float
	float GetDegrees();

	//! Set the main color of the object
	//! White = Textures only
	//! @param color Set the color as glm::vec3
	void ChangeMainColor(glm::vec3 color);
	//! Set the main color of the object
	//! White = Textures only
	//! @param color Set the color as Vector3
	void ChangeMainColor(Vector3 color);
	
	//! Set the main color of the object
	//! White = Textures only
	//! @param color Set color as GameObject::ObjectColor
	//! @see GameObject::ObjectColor
	void ChangeMainColor(ObjectColor color);

	//! Returns the main color of the object
	//! @return Main Color of the object as glm::vec3
	glm::vec3 GetMainColor();
	//! Returns the main color of the object
	//! @return Main Color of the object as Vector3
	Vector3 GetMainColorVector3();

	//! Set rotation relative to an object
	//! @param pos Insert the position as glm::vec3
	void LookAt(glm::vec3 pos);
	//! Set rotation relative to an object
	//! @param pos Insert the position as Vector3
	void LookAt(Vector3 pos);

	//! Set rotation relative to an object
	//! @param pos Insert the position as glm::vec2
	void LookAt(glm::vec2 pos);
	//! Set rotation relative to an object
	//! @param pos Insert the position as Vector2
	void LookAt(Vector2 pos);

	//! Set rotation relative to an object
	//! @param x Insert x value
	//! @param y Insert y value
	//! @param z Insert z value
	void LookAt(float x, float y, float z);

	//! Show or hide model
	//! @param value Insert value as bool
	void SetActive(bool value);

	//! Return true if model is active
	//! @return Returns active as bool
	bool IsActive();

	//! Rotate object round value
	//! @param rotation Insert rotation as glm::vec3
	void Rotate(glm::vec3 rotation);
	//! Rotate object round value
	//! @param rotation Insert rotation as Vector3
	void Rotate(Vector3 rotation);

	//! Load default texture again and delete the old one in ram
	//! Need to be called by the gameplay programmer!
	void ReloadDefaultTexture();

	//! Set normal map for mesh
	//! @param normal Set file location to normal as std::string
	void SetNormalMap(std::string normal);

	//! Set if the object should render transparent/semi-transparent objects
	//! @param value Set value as bool
	void UseBlending(bool value);

	//! Set if the object should render with a parallax map
	//! @param value Set value as bool
	void UseParallaxMapping(bool value);

	//! Get if the object renders transparent/semi-transparent objects
	//! @return Returns if object uses blending as bool
	bool GetUseBlending();

	//! Returns a pointer to an array with all vertices
	//! @return Returns vertices as float pointer (float*)
	float* GetVertices();

	//! Returns a pointer to an array with all indices
	//! @return Returns indices as unsigned int pointer (unsigned int*)
	unsigned int* GetIndices();

	//! Set the default texture
	//! @param path Insert file location as std::string
	void SetDefaultTexture(std::string path);

	//! Get path to default texture
	//! @return Returns file location as std::string
	std::string GetDefaultTexture();

	//! Use normal map
	//! @param value Insert value as bool
	void UseNormalMaps(bool value);
	//! Bool for rendering normal maps
	//! @return Returns if the object uses normal maps
	bool GetUseNormalMaps();
	//! Bool for rendering parallax maps
	//! @return Returns if the object should render with parallax
	bool GetParallaxMap();
	
	//! Get file location 
	//! @return Returns the file location as char*
	char* GetFileName();

	//! Set file location of the mesh
	//! @param fileLocation Insert file location as char pointer (char*)
	void SetFileLocation(char* fileLocation);

	//! Set file location of the mesh
	//! @param fileLocation Insert the file location as std::string
	void SetFileLocation(std::string fileLocation);

	//! Load model
	//! Model is automatically loaded
	//! @return Returns NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR LoadModel();

	//! Load model from string
	//! Model is NOT automatically loaded
	//! @param fileName Insert file location as const std::string&
	//! @return Returns NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR LoadModel(const std::string& fileName);

	//! Use Primitive as Object
	//! @param primitive Insert ObjectPrimitive
	//! @see ObjectPrimitive
	void UsePrimitive(ObjectPrimitive primitive);

	//! Render the model
	//! Is called automatically
	void RenderModel();

	//! Delete all data on the ram
	void ClearModel();

	~GameObject();

private:
	//! Load single object
	void LoadNode(aiNode *node, const aiScene *scene);
	//! Load mesh
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	//! Load materials
	void LoadMaterials(const aiScene *scene);

	//! Generate vertices, indices & normals
	void PrimitiveCube();
	//! Generate vertices, indices & normals
	void PrimitiveSphere();
	//! Generate vertices, indices & normals
	void PrimitivePlane();

	//! Mesh list
	std::vector<Mesh*> meshList;
	//! Texture list
	std::vector<Texture*> textureList;
	//! Material index
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
	bool useParallaxMap = false;
	bool useBitangent = true;
	bool useNormalMap = true;
	bool useBlending = false;

	glm::mat4 model = glm::mat4();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rota = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 mainColor = glm::vec3(1.0f, 1.0f, 1.0f);

	std::string defaultPath = "Textures/dev.jpg";
	std::string defaultNormalPath = "Textures/normal.jpg";

	Texture normal;
};