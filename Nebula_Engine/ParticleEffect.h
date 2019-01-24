#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

//! Struct for a particle
struct Particle
{
	glm::vec3 Position, Velocity;
	glm::vec4 Color;
	float Life;
};

//! Main class to create a particle effect
class ParticleEffect
{
public:
	ParticleEffect(int size, glm::vec3 pos, glm::vec3 lookAt);

	//! Add a new texture to the object
	//! Set the duration for the particle texture
	void AddTexture(const Texture texture, const float time);
	//! Load all textures
	//! Called automaticly
	void LoadTextures();
	//! Use in your update
	//! 
	void ParticleUpdate(float deltaTime);
	//! Delete one particle
	//! 
	void DeleteParticle(int i);

	~ParticleEffect();

private:
	void GeneratePlane();

private:
	std::vector<Texture> textureList;
	std::vector<float> timeList;

	glm::vec3 position;
	glm::vec3 camera;

	glm::mat4 model;

	Mesh* mesh;
	Shader* shader;

	int size;
};

