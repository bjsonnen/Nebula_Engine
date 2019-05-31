#include "GameObject.h"

#include "Util.h"

NE::GameObject::GameObject()
{
	location = "";
	objectName = "GameObject";
}

NE::GameObject::GameObject(char* filelocation)
{
	location = filelocation;
	objectName = "GameObject";
}

glm::vec3 NE::GameObject::GetPosition()
{
	return pos;
}

Vector3 NE::GameObject::GetPositionVector3()
{
	return Vector3(pos.x, pos.y, pos.z);
}

glm::vec3 NE::GameObject::GetRotation()
{
	return rota;
}

Vector3 NE::GameObject::GetRotationVector3()
{
	return glm::vec3(rota.x, rota.y, rota.y);
}

glm::vec3 NE::GameObject::GetScale()
{
	return scale;
}

Vector3 NE::GameObject::GetScaleVector3()
{
	return glm::vec3(scale.x, scale.y, scale.z);
}

int NE::GameObject::GetVerticesCount()
{
	return verticesCount;
}

int NE::GameObject::GetIndicesCount()
{
	return indicesCount;
}

void NE::GameObject::SetPosition(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

void NE::GameObject::SetPosition(glm::vec3 position)
{
	pos = position;
}

void NE::GameObject::SetPosition(Vector3 position)
{
	pos = position.ToGlm();
}

void NE::GameObject::SetRotation(float x, float y, float z)
{
	rota = glm::vec3(x, y, z);
}

void NE::GameObject::SetRotation(glm::vec3 rotation)
{
	rota = rotation;
}

void NE::GameObject::SetRotation(Vector3 rotation)
{
	rota = rotation.ToGlm();
}

void NE::GameObject::SetDegrees(float value)
{
	rotaDegrees = value;
}

void NE::GameObject::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

void NE::GameObject::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

void NE::GameObject::SetScale(Vector3 scale)
{
	this->scale = scale.ToGlm();
}

bool NE::GameObject::GetRenderNormalMaps()
{
	return useBitangent;
}

void NE::GameObject::SetNormalMap(char * location)
{
	normal.SetFileLocation(location);
}

float NE::GameObject::GetDegrees()
{
	return rotaDegrees;
}

void NE::GameObject::ChangeMainColor(glm::vec3 color)
{
	mainColor = color;
}

void NE::GameObject::ChangeMainColor(Vector3 color)
{
	mainColor = color.ToGlm();
}

void NE::GameObject::ChangeMainColor(ObjectColor color)
{
	switch (color)
	{
	case ObjectColor::Red:
		mainColor = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case ObjectColor::Blue:
		mainColor = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case ObjectColor::Green:
		mainColor = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case ObjectColor::Gray:
		mainColor = glm::vec3(0.5f, 0.5f, 0.5f);
		break;
	case ObjectColor::Purple:
		mainColor = glm::vec3(0.70196078f, 0.13f, 0.64313725f);
		break;
	case ObjectColor::Yellow:
		mainColor = glm::vec3(0.81176470f, 0.83921568f, 0.09411764f);
		break;
	case ObjectColor::Orange:
		mainColor = glm::vec3(0.839215686f, 0.53f, 0.094117647f);
		break;
	case ObjectColor::Black:
		mainColor = glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case ObjectColor::White:
		mainColor = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	}
}

glm::vec3 NE::GameObject::GetMainColor()
{
	return mainColor;
}

Vector3 NE::GameObject::GetMainColorVector3()
{
	return Vector3(mainColor.x, mainColor.y, mainColor.z);
}

void NE::GameObject::LookAt(glm::vec3 pos)
{
	glm::vec3 dir = this->pos - pos;
	rota = dir;
}

void NE::GameObject::LookAt(Vector3 pos)
{
	glm::vec3 dir = this->pos - pos.ToGlm();
	rota = dir;
}

void NE::GameObject::LookAt(glm::vec2 pos)
{
	glm::vec3 dir = this->pos - glm::vec3(pos.x, pos.y, 0.0f);
	rota = dir;
}

void NE::GameObject::LookAt(Vector2 pos)
{
	glm::vec3 dir = this->pos - glm::vec3(pos.x, pos.y, 0.0f);
	rota = dir;
}

void NE::GameObject::LookAt(float x, float y, float z)
{
	glm::vec3 dir = this->pos - glm::vec3(x, y, z);
	rota = dir;
}

void NE::GameObject::SetActive(bool value)
{
	activeModel = value;
}

bool NE::GameObject::IsActive()
{
	return activeModel;
}

void NE::GameObject::Rotate(glm::vec3 rotation)
{
	rota += rotation;
}

void NE::GameObject::Rotate(Vector3 rotation)
{
	rota += rotation.ToGlm();
}

void NE::GameObject::ReloadDefaultTexture()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->SetFileLocation(defaultPath);
		textureList[i]->LoadTexture();
	}
	normal.LoadTexture();
}

void NE::GameObject::SetNormalMap(std::string normal)
{
	//Texture test = Texture(normal.c_str());
	//if (meshToTex.size() == 0)
	//	meshToTex.push_back(0);
	//else
	//	meshToTex.push_back(meshList.size() - 1);
	//textureList.push_back(&test);
}

bool NE::GameObject::GetUseBlending()
{
	return useBlending;
}

void NE::GameObject::UseBlending(bool value)
{
	useBlending = value;
}

void NE::GameObject::UseParallaxMapping(bool value)
{
	useParallaxMap = value;
}

float * NE::GameObject::GetVertices()
{
	return nullptr;
}

unsigned int * NE::GameObject::GetIndices()
{
	return nullptr;
}

void NE::GameObject::SetDefaultTexture(std::string path)
{
	defaultPath = path;
}

std::string NE::GameObject::GetDefaultTexture()
{
	return defaultPath;
}

void NE::GameObject::UseNormalMaps(bool value)
{
	useNormalMap = value;
}

bool NE::GameObject::GetUseNormalMaps()
{
	return useNormalMap;
}

bool NE::GameObject::GetParallaxMap()
{
	return useParallaxMap;
}

void NE::GameObject::RenderModel()
{
	if (activeModel)
	{
		for (size_t i = 0; i < meshList.size(); i++)
		{
			unsigned int materialIndex = meshToTex[i];

			if (materialIndex < textureList.size() && textureList[materialIndex])
			{
				textureList[materialIndex]->UseTexture();
				normal.UseTexture(GL_TEXTURE2);
			}
			meshList[i]->RenderMesh();
		}
	}
}

char* NE::GameObject::GetFileName()
{
	return location;
}

void NE::GameObject::SetFileLocation(char* fileLocation)
{
	location = fileLocation;
}

void NE::GameObject::SetFileLocation(std::string fileLocation)
{
	location = (char*)fileLocation.c_str();
}

std::string NE::GameObject::GetObjectName()
{
	return objectName;
}

void NE::GameObject::SetObjectName(std::string name)
{
	objectName = name;
}

NE_ERROR NE::GameObject::LoadModel()
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", location, importer.GetErrorString());
		return NE_FALSE;
	}

	normal = NE::Texture("Textures/normal.jpg");

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return NE_OK;
}

NE_ERROR NE::GameObject::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

	if (!scene)
	{
		printf("Model (%s) failed to load!", fileName, importer.GetErrorString());
		return NE_FALSE;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return NE_OK;
}

void NE::GameObject::UsePrimitive(ObjectPrimitive primitive)
{
	switch (primitive)
	{
	case ObjectPrimitive::Cube:
		PrimitiveCube();
		usePrimitive = true;
		break;
	case ObjectPrimitive::Plane:
		PrimitivePlane();
		usePrimitive = true;
		break;
	case ObjectPrimitive::Sphere:
		PrimitiveSphere();
		usePrimitive = true;
		break;
	}
}

void NE::GameObject::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void NE::GameObject::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	// Primitive
	if (strlen(location) == 0)
	{
		return;
	}

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
		
		// Add Tangents and Bitangents if available
		if (mesh->HasTangentsAndBitangents())
		{
			vertices.insert(vertices.end(), { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z });
			vertices.insert(vertices.end(), { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z });
			//printf("Bitangent X: %d // Bitangent Y: %d // Bitangent Z: %d\n", mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
		}
		else if (useBitangent)
		{
			useBitangent = false;
			vertices.insert(vertices.end(), { 0.0f, 0.0f, 0.0f});
			vertices.insert(vertices.end(), { 0.0f, 0.0f, 0.0f});
			NE_ERROR_CHECK(NE_UNABLE_BITANGENT);
			printf("Unable to calculate Tangents and Bitangents for object %s\n", GetFileName());
		}
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	verticesCount += vertices.size();
	indicesCount += indices.size();

	NE::Mesh* newMesh = new NE::Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void NE::GameObject::LoadMaterials(const aiScene * scene)
{
	textureList.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				textureList[i] = new NE::Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture())
				{
					NE_ERROR_CHECK(NE_ERROR::NE_TEXTURE);
					delete textureList[i];
					textureList[i] = nullptr;
				}
				normal.LoadTexture();
			}
		}
		//if (material->GetTextureCount(aiTextureType_NORMALS))
		//{
		//	aiString path;
		//	if (material->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS)
		//	{
		//		int idx = std::string(path.data).rfind("\\");
		//		std::string filename = std::string(path.data).substr(idx + 1);
		//		std::string texPath = std::string("Textures/") + filename;

		//		normal.SetFileLocation(texPath);

		//		if (!normal.LoadTexture())
		//		{
		//			NE_ERROR_CHECK(NE_ERROR::NE_TEXTURE);
		//			normal.SetFileLocation(defaultNormalPath);
		//			normal.LoadTexture();
		//		}
		//	}
		//}
		//else
		//{
		//	normal.SetFileLocation(defaultNormalPath);
		//	normal.LoadTexture();
		//}

		// if texture is not available, use default
		if (!textureList[i])
		{
			textureList[i] = new NE::Texture(defaultPath.c_str());
			textureList[i]->LoadTexture();
			normal.LoadTexture();
		}
	}
}

void NE::GameObject::PrimitiveCube()
{
}

void NE::GameObject::PrimitiveSphere()
{
}

void NE::GameObject::PrimitivePlane()
{
	NE::Util util;

	float vertices[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	util.CalculateNormals(indices, 6, vertices, 32, 8, 5);

	NE::Mesh* mesh = new NE::Mesh();
	mesh->CreateMesh(vertices, indices, 32, 6);
	meshList.push_back(mesh);
	delete mesh;
}

void NE::GameObject::ClearModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}

NE::GameObject::~GameObject()
{
}
