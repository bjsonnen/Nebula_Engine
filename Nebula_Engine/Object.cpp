#include "Object.h"

#include "Util.h"

Object::Object()
{
	location = "";
}

Object::Object(char* filelocation)
{
	location = filelocation;
}

void Object::Init()
{
	location = "";
	activeModel = true;
}

void Object::Update()
{
}

int Object::GetVerticesCount()
{
	return verticesCount;
}

int Object::GetIndicesCount()
{
	return indicesCount;
}

void Object::ReloadDefaultTexture()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->SetFileLocation(defaultPath);
		textureList[i]->LoadTexture();
	}
}

void Object::SetNormalMap(std::string normal)
{
	//Texture test = Texture(normal.c_str());
	//if (meshToTex.size() == 0)
	//	meshToTex.push_back(0);
	//else
	//	meshToTex.push_back(meshList.size() - 1);
	//textureList.push_back(&test);
}

float * Object::GetVertices()
{
	return nullptr;
}

unsigned int * Object::GetIndices()
{
	return nullptr;
}

void Object::SetDefaultTexture(std::string path)
{
	defaultPath = path;
}

std::string Object::GetDefaultTexture()
{
	return defaultPath;
}

NE_ERROR Object::RenderModel()
{
	if (activeModel)
	{
		if (meshList.size() == 0)
			return NE_RENDERER;

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
	else
		return NE_RENDERER;
	return NE_OK;
}

char* Object::GetFileName()
{
	return location;
}

void Object::SetFileLocation(char* fileLocation)
{
	location = fileLocation;
}

void Object::SetFileLocation(std::string fileLocation)
{
	location = (char*)fileLocation.c_str();
}

NE_ERROR Object::LoadModel()
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices /*| aiProcess_CalcTangentSpace*/);

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

NE_ERROR Object::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices/* | aiProcess_CalcTangentSpace*/);

	if (!scene)
	{
		printf("Model (%s) failed to load!", fileName, importer.GetErrorString());
		return NE_FALSE;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return NE_OK;
}

void Object::UsePrimitive(ObjectPrimitive primitive)
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

void Object::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
		//float x = scene->mMeshes[i]->mBitangents->x;
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Object::LoadMesh(aiMesh * mesh, const aiScene * scene)
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

	NE::Mesh* newMesh = new NE::Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Object::LoadMaterials(const aiScene * scene)
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
			textureList[i] = new NE::Texture(defaultPath.c_str());
			textureList[i]->LoadTexture();
			normal.LoadTexture();
		}
	}
}

void Object::PrimitiveCube()
{
}

void Object::PrimitiveSphere()
{
}

void Object::PrimitivePlane()
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

void Object::ClearModel()
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

Object::~Object()
{
}
