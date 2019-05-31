#pragma once

#include "GameObject.h"

#include <map>
#include <vector>
#include <sstream>

class GameObjectList
{
public:
	GameObjectList();

	void Add(GameObject& object);
	void Remove(GameObject& object);
	int GetSize();
	GameObject* Find(GameObject& object);
	GameObject* FindAtIndex(int i);

	~GameObjectList();

private:
	std::map<int, GameObject*> objectList;

	int ParseInt(std::string s);
};

