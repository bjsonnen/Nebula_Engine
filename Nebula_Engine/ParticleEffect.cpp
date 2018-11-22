#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(int size, glm::vec3 pos, glm::vec3 lookAt)
{
	textureList.resize(size);
	timeList.resize(size);
	position = pos;
	camera = lookAt;
	this->size = size;

	shader->CreateFromFiles("Shaders/particle.vert", "Shaders/particle.frag");
}

void ParticleEffect::AddTexture(const Texture texture, const float time)
{
	textureList.push_back(texture);
	timeList.push_back(time);
}

void ParticleEffect::LoadTextures()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i].LoadTexture();
	}
}

void ParticleEffect::ParticleUpdate(float deltaTime)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		if (timeList[i] <= 0.0f)
		{
			textureList[i].~Texture();
		}
		else
		{
			timeList[i] -= deltaTime;
		}
	}

	// LOOK AT CAMERA

	// USE PARTICLE
	shader->UseShader();
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i].UseTexture();
		glBindVertexArray(mesh->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
		glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndices(), GL_UNSIGNED_BYTE, 0, size);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glUseProgram(0);
}

void ParticleEffect::DeleteParticle(int i)
{
	textureList[i].~Texture();
	timeList[i] = 0.0f; // ToDo
}


ParticleEffect::~ParticleEffect()
{
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i].~Texture();
	}
	delete shader;
}

void ParticleEffect::GeneratePlane()
{
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
	
	mesh->CreateMesh(vertices, indices, 32, 6);
}
