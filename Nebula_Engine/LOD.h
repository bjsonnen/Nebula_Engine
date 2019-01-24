#pragma once

#include <vector>
#include <string>

#include "GameObject.h"
#include "Camera.h"

class LOD
{
public:
	//! Create an LOD System
	//! Camera needed
	LOD();
	//! Create an LOD System
	LOD(Camera* mainCam);

	//! Sets the current camera
	void SetCamera(Camera* mainCam);
	//! Returns the current camera
	Camera* GetCamera();

	//! Create your automatic lod
	void SetLod(std::vector<std::string> fileLocation, std::vector<float> distance);

	//! Update the current object
	//! Need to be called once per frame
	void Update();

	void SetPosition();
	void SetRotation();
	void SetScale();

	//! Activate the lod
	void SetActive(bool value);
	//! If the lod is active
	bool GetActive();

	~LOD();

private:
	Camera * mainCamera;
	std::vector<std::string> paths;
	std::vector<float> distance;
	std::vector<GameObject> objects;

	int activeObject = 0;
	int count = 0;
	bool activated = true;
};

