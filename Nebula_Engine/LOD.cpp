#include "LOD.h"



LOD::LOD()
{
}

LOD::LOD(Camera * mainCam)
{
	mainCamera = mainCam;
}

void LOD::SetCamera(Camera * mainCam)
{
	mainCamera = mainCam;
}

Camera * LOD::GetCamera()
{
	return mainCamera;
}

void LOD::SetLod(std::vector<std::string> fileLocation, std::vector<float> distance)
{
	this->paths = fileLocation;
	this->distance = distance;
	count = fileLocation.size();

	for (int i = 0; i < count; i++)
	{
		GameObject go = GameObject();
		go.SetFileLocation(fileLocation[i]);
		objects.push_back(go);
	}

}

void LOD::Update()
{
	float camDistance = 0.0f;
	float tmp = 0.0f;
	int lod = 0;
	for (int i = 0; i < count; i++)
	{
		camDistance = glm::distance(mainCamera->GetCameraPosition(), objects[0].GetPosition());
		if (camDistance > tmp)
		{
			tmp = camDistance;
			lod = i;
		}
	}
	objects[activeObject].SetActive(false);
	activeObject = lod;
	objects[activeObject].SetActive(true);
}

void LOD::SetActive(bool value)
{
	activated = value;
}

bool LOD::GetActive()
{
	return activated;
}


LOD::~LOD()
{
}
