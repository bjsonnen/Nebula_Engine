#include "GameObject.h"

#include "Util.h"

GameObject::GameObject()
{
	location = "";
}

GameObject::GameObject(char* filelocation)
{
	location = filelocation;
}

glm::vec3 GameObject::GetPosition()
{
	return pos;
}

glm::vec3 GameObject::GetRotation()
{
	return rota;
}

glm::vec3 GameObject::GetScale()
{
	return scale;
}

int GameObject::GetVerticesCount()
{
	return verticesCount;
}

int GameObject::GetIndicesCount()
{
	return indicesCount;
}

void GameObject::SetPosition(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

void GameObject::SetPosition(glm::vec3 position)
{
	pos = position;
}

void GameObject::SetRotation(float x, float y, float z)
{
	rota = glm::vec3(x, y, z);
}

void GameObject::SetRotation(glm::vec3 rotation)
{
	rota = rotation;
}

void GameObject::SetDegrees(float value)
{
	rotaDegrees = value;
}

void GameObject::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

void GameObject::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

float GameObject::GetDegrees()
{
	return rotaDegrees;
}

void GameObject::LookAt(glm::vec3 pos)
{
	glm::vec3 dir = this->pos - pos;
	rota = dir;
}

void GameObject::LookAt(glm::vec2 pos)
{
	glm::vec3 dir = this->pos - glm::vec3(pos.x, pos.y, 0.0f);
	rota = dir;
}

void GameObject::LookAt(float x, float y, float z)
{
	glm::vec3 dir = this->pos - glm::vec3(x, y, z);
	rota = dir;
}

void GameObject::SetActive(bool value)
{
	activeModel = value;
}

bool GameObject::IsActive()
{
	return activeModel;
}

void GameObject::Rotate(glm::vec3 rotation)
{
	rota += rotation;
}

void GameObject::ReloadDefaultTexture()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->SetFileLocation(defaultPath);
		textureList[i]->LoadTexture();
	}
}

void GameObject::SetNormalMap(std::string normal)
{
	//Texture test = Texture(normal.c_str());
	//if (meshToTex.size() == 0)
	//	meshToTex.push_back(0);
	//else
	//	meshToTex.push_back(meshList.size() - 1);
	//textureList.push_back(&test);
}

float * GameObject::GetVertices()
{
	return nullptr;
}

unsigned int * GameObject::GetIndices()
{
	return nullptr;
}

void GameObject::SetDefaultTexture(std::string path)
{
	defaultPath = path;
}

std::string GameObject::GetDefaultTexture()
{
	return defaultPath;
}

void GameObject::RenderModel()
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

char* GameObject::GetFileName()
{
	return location;
}

void GameObject::SetFileLocation(char* fileLocation)
{
	location = fileLocation;
}

void GameObject::SetFileLocation(std::string fileLocation)
{
	location = (char*)fileLocation.c_str();
}

bool GameObject::LoadModel()
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices /*| aiProcess_CalcTangentSpace*/);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", location, importer.GetErrorString());
		return false;
	}

	normal = Texture("Textures/normal.jpg");

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return true;
}

bool GameObject::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("Model (%s) failed to load!", fileName, importer.GetErrorString());
		return false;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return true;
}

void GameObject::UsePrimitive(ObjectPrimitive primitive)
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

void GameObject::LoadNode(aiNode * node, const aiScene * scene)
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

void GameObject::LoadMesh(aiMesh * mesh, const aiScene * scene)
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

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void GameObject::LoadMaterials(const aiScene * scene)
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

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture())
				{
					printf("Unable to load texture: %s\n", texPath);
					delete textureList[i];
					textureList[i] = nullptr;
				}
				normal.LoadTexture();
			}
		}

		// if texture is not available, use default
		if (!textureList[i])
		{
			textureList[i] = new Texture(defaultPath.c_str());
			textureList[i]->LoadTexture();
			normal.LoadTexture();
		}
	}
}

void GameObject::PrimitiveCube()
{
}

void GameObject::PrimitiveSphere()
{
}

void GameObject::PrimitivePlane()
{
	Util util;

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

	Mesh* mesh = new Mesh();
	mesh->CreateMesh(vertices, indices, 32, 6);
	meshList.push_back(mesh);
	delete mesh;
}

void GameObject::ClearModel()
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

GameObject::~GameObject()
{
}
