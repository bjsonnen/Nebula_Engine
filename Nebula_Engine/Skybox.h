#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Mesh.h"
#include "Shader.h"

//! Main class for the skybox
class Skybox
{
public:
	//! Create Skybox with standard parameters
	Skybox();

	//! Create Skybox with specific parameters
	//! @param faceLocations Insert all 6 textures here as std::vector<std::string> 
	Skybox(std::vector<std::string> faceLocations);

	//! Draw Skybox
	//! @param viewMatrix Insert the view matrix as glm::mat4 (4x4 matrix)
	//! @param projectionMatrix Insert the projectionMatrix as glm::mat4 (4x4 matrix)
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	Mesh* skyMesh;
	Shader* skyShader;

	unsigned int textureId;
};

