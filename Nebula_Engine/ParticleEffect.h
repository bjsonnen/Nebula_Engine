//#pragma once
//#include <vector>
//#include <glm/glm.hpp>
//
//#include "Mesh.h"
//#include "Texture.h"
//#include "Shader.h"
//
////! Struct for a particle
//struct Particle
//{
//	//! Insert position of the particle
//	Vector3 Position;
//	//! Insert direction of the particle
//	Vector3 Direction;
//	//! Insert velocity of the particle
//	Vector3 Velocity;
//	//! Insert rotation of the particle
//	Vector3 Rotation;
//	//! Insert scale of the particle
//	Vector3 Scale;
//	//! Insert color of the particle
//	//! Only use the color if there is not texture
//	glm::vec4 Color;
//	//! Insert texture for the particle
//	Texture Texture;
//	//! Insert life time of the particle
//	float Life;
//};
//
////! Main class to create a particle effect
//class ParticleEffect
//{
//public:
//	//! Create a new particle effect with standard parameters
//	ParticleEffect() {}
//	//! Create a new particle effect with specific parameters
//	//! @param particleList Insert a std::vector of particles as std::vector<Particle*>*
//	//! @param respawn Insert respawn timer as float, use -1 for never respawn and 0 for immediatly respawn
//	//! @param lifeTimeAfterRespawn Insert life time after a respawn as float
//	//! @param useColor Insert bool if the particle shader should use the color of the texture
//	//! @param cameraPosition Insert current camera position as glm::vec3
//	ParticleEffect(std::vector<Particle*>* particleList, float respawn, float lifeTimeAfterRespawn, 
//		bool useColor, glm::vec3 cameraPosition);
//	//! Create a new particle effect with specific parameters
//	//! @param particleList Insert a std::vector of particles as std::vector<Particle*>*
//	//! @param respawn Insert respawn timer as float, use -1 for never respawn and 0 for immediatly respawn
//	//! @param lifeTimeAfterRespawn Insert life time after a respawn as float
//	//! @param useColor Insert bool if the particle shader should use the color of the texture
//	//! @param cameraPosition Insert current camera position as Vector3
//	ParticleEffect(std::vector<Particle*>* particleList, float respawn, float lifeTimeAfterRespawn,
//		bool useColor, Vector3 cameraPosition);
//
//	//! Update the current particle effect to another particle effect
//	//! @param particleList Insert current std::vector list of Particle* as std::vector<Particle*>*
//	void InsertNewParticleList(std::vector<Particle*>* particleList);
//
//	//! Det the respawn time of the hole particle effect
//	//! @param respawn Insert respawn timer as float, use -1 for never respawn and 0 for immediatly respawn
//	void SetRespawnTimer(float respawn);
//	
//	//! Load all textures
//	//! Called automaticly
//	void LoadTextures();
//	//! Use in your update
//	//! @param deltaTime Insert deltatime as float
//	//! @see Window::GetDeltaTime()
//	void ParticleUpdate(float deltaTime);
//	//! Delete one particle
//	//! @param index Insert index of the particle effect as int
//	void DeleteParticle(int index);
//
//	//! Set new respawn timer after respawn
//	//! @param value Insert new respawn timer as float
//	void SetRespawnTimerAfterRespawn(float value);
//
//	//! Get the current position of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current position of the particle as glm::vec3
//	glm::vec3 GetPosition(int index);
//	//! Get the current position of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current position of the particle as Vector3
//	Vector3 GetPositionVector3(int index);
//	//! Get the current rotation of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current rotation of the particle as glm::vec3
//	glm::vec3 GetRotation(int index);
//	//! Get the current rotation of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current rotation of the particle as Vector3
//	Vector3 GetRotationVector3(int index);
//	//! Get the current scale of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current scale of the particle as glm::vec3
//	glm::vec3 GetScale(int index);
//	//! Get the current scale of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current scale of the particle as Vector3
//	Vector3 GetScaleVector3(int index);
//	//! Get the current texture of the particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current texture of the particle as Texture* (Texture pointer)
//	//! @see Texture
//	Texture* GetTexture(int index);
//	//! Get the current life time of an particle effect
//	//! @param index Insert the index of the particle effect as int
//	//! @return Returns the current life time of the particle as float
//	float GetLife(int index);
//
//	//! Get the current life time after an object has respawned
//	//! @return Returns the current respawn life timer after an object respawned
//	float GetRespawnTimerAfterRespawn();
//
//	//! Particle at index should look at rotation
//	//! @param index Insert index of particle effect as int
//	//! @param target Insert the target to look at as glm::vec3
//	void LookAt(int index, glm::vec3 target);
//	//! Particle at index should look at rotation
//	//! @param index Insert index of particle effect as int
//	//! @param target Insert the target to look at as Vector3
//	void LookAt(int index, Vector3 target);
//
//	~ParticleEffect();
//
//private:
//	void GeneratePlane();
//
//private:
//	std::vector<Particle*>* particleList;
//
//	glm::vec3 cameraPosition;
//
//	glm::mat4 model;
//	glm::mat4 projection;
//
//	Mesh* mesh;
//	Shader* shader;
//
//	float respawnTimer;
//	float respawnTimeAfterRespawn;
//	
//	bool useColor = false;
//	bool neverRespawn = true;
//};