#include "ECManager.h"

int Entity::GetVerticesCount()
{
	return verticesCount;
}

int Entity::GetIndeciesCount()
{
	return indicesCount;
}

void Entity::ReloadDefaultTexture()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->SetFileLocation(defaultPath);
		textureList[i]->LoadTexture();
	}
}

void Entity::SetNormalMap(char * path)
{
}

float * Entity::GetVertices()
{
	return nullptr;
}

unsigned int * Entity::GetIndices()
{
	return nullptr;
}

void Entity::SetDefaultTexture(char * path)
{
	defaultPath = path;
}

char * Entity::GetDefaultTexture()
{
	return defaultPath;
}

char * Entity::GetFileName()
{
	return location;
}

void Entity::SetFileLocation(char * fileLocation)
{
	location = fileLocation;
}

NE_ERROR Entity::LoadModel()
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(location, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices /*| aiProcess_CalcTangentSpace*/);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", location, importer.GetErrorString());
		return NE_FALSE;
	}

	normal = Texture("Textures/normal.jpg");

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return NE_OK;
}

NE_ERROR Entity::LoadModel(const char * fileName)
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

void Entity::UsePrimitibe(ObjectPrimitive primitive)
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

NE_ERROR Entity::RenderModel()
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

void Entity::ClearModel()
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

void Entity::LoadNode(aiNode * node, const aiScene * scene)
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

void Entity::LoadMesh(aiMesh * mesh, const aiScene * scene)
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

void Entity::LoadMaterials(const aiScene * scene)
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
			textureList[i] = new Texture(defaultPath);
			textureList[i]->LoadTexture();
			normal.LoadTexture();
		}
	}
}

void Entity::PrimitiveCube()
{
}

void Entity::PrimitiveSphere()
{
}

void Entity::PrimitivePlane()
{
}
