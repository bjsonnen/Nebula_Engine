#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(std::vector<Particle*>* particleList, float respawn, float lifeTimeAfterRespawn, 
	bool useColor, glm::vec3 cameraPosition)
{
	this->useColor = useColor;
	this->particleList = particleList;
	this->cameraPosition = cameraPosition;
	respawnTimeAfterRespawn = lifeTimeAfterRespawn;
	SetRespawnTimer(respawn);
}

ParticleEffect::ParticleEffect(std::vector<Particle*>* particleList, float respawn, float lifeTimeAfterRespawn, bool useColor, Vector3 cameraPosition)
{
}

void ParticleEffect::InsertNewParticleList(std::vector<Particle*>* particleList)
{
	this->particleList = particleList;
}

void ParticleEffect::SetRespawnTimer(float respawn)
{
	if (respawnTimer == -1.0f)
		neverRespawn = true;
	else if (respawnTimer >= 0.0f)
	{
		neverRespawn = false;
		respawnTimer = respawn;
	}
}

void ParticleEffect::LoadTextures()
{
	for (int i = 0; i < particleList->size(); i++)
	{
		particleList->at(i)->Texture.LoadTexture();
	}
}

void ParticleEffect::ParticleUpdate(float deltaTime)
{
	for (int i = 0; i < particleList->size(); i++)
	{
		particleList->at(i)->Life -= deltaTime;
		if (particleList->at(i)->Life < respawnTimer && !neverRespawn)
			particleList->at(i)->Life = respawnTimeAfterRespawn;
		else if (particleList->at(i)->Life < 0.0f && neverRespawn)
			DeleteParticle(i);
	}
	
	// USE PARTICLE
	shader->UseShader();
	for (int i = 0; i < particleList->size(); i++)
	{
		model = glm::mat4();
		model = glm::translate(model, particleList->at(i)->Position.ToGlm());
		model = glm::rotate(model, deltaTime, cameraPosition);
		model = glm::scale(model, particleList->at(i)->Scale.ToGlm());

		particleList->at(i)->Texture.UseTexture();
		shader->SetMatrix("model", glm::mat4());
		shader->SetMatrix("projection", glm::mat4());
		shader->SetVector4("color", particleList->at(i)->Color);
		shader->SetBool("useColor", useColor);
		glBindVertexArray(mesh->GetVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
		glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndices(), GL_UNSIGNED_BYTE, 0, 1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glUseProgram(0);
}

void ParticleEffect::DeleteParticle(int index)
{
	particleList->erase(particleList->begin() + index);
}

void ParticleEffect::SetRespawnTimerAfterRespawn(float value)
{
	respawnTimeAfterRespawn = value;
}

glm::vec3 ParticleEffect::GetPosition(int index)
{
	return particleList->at(index)->Position.ToGlm();
}

Vector3 ParticleEffect::GetPositionVector3(int index)
{
	return particleList->at(index)->Position;
}

glm::vec3 ParticleEffect::GetRotation(int index)
{
	return particleList->at(index)->Rotation.ToGlm();
}

Vector3 ParticleEffect::GetRotationVector3(int index)
{
	return particleList->at(index)->Rotation;
}

glm::vec3 ParticleEffect::GetScale(int index)
{
	return particleList->at(index)->Scale.ToGlm();
}

Vector3 ParticleEffect::GetScaleVector3(int index)
{
	return particleList->at(index)->Scale;
}

Texture * ParticleEffect::GetTexture(int index)
{
	return &particleList->at(index)->Texture;
}

float ParticleEffect::GetLife(int index)
{
	return particleList->at(index)->Life;
}

float ParticleEffect::GetRespawnTimerAfterRespawn()
{
	return respawnTimeAfterRespawn;
}

void ParticleEffect::LookAt(int index, glm::vec3 target)
{
	particleList->at(index)->Rotation = Vector3(target.x, target.y, target.z);
}

void ParticleEffect::LookAt(int index, Vector3 target)
{
	particleList->at(index)->Rotation = target;
}

ParticleEffect::~ParticleEffect()
{
	delete[] particleList;
	delete shader;
	delete mesh;
}

void ParticleEffect::GeneratePlane()
{
	float vertices[] = 
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = 
	{
		0, 1, 2, 
		0, 2, 3
	};
	
	mesh->CreateMesh(vertices, indices, 56, 6);
}