#include "GameObjectList.h"



GameObjectList::GameObjectList()
{
}

void GameObjectList::Add(GameObject& object)
{
	objectList[objectList.size()] = &object;
	object.SetObjectName("GameObject " + std::to_string(objectList.size()));
}

void GameObjectList::Remove(GameObject& object)
{
	int i = ParseInt(object.GetObjectName());
	objectList.erase(i - 1);
}

int GameObjectList::GetSize()
{
	return objectList.size();
}

GameObject * GameObjectList::Find(GameObject& object)
{
	int i = ParseInt(object.GetObjectName());
	return objectList.at(i - 1);
}

GameObject * GameObjectList::FindAtIndex(int i)
{
	return objectList.at(i);
}


GameObjectList::~GameObjectList()
{
}

int GameObjectList::ParseInt(std::string s)
{
	std::stringstream ss;

	ss << s;

	std::string tmp;
	int found = 0;
	while (!ss.eof())
	{
		ss >> tmp;
		std::stringstream(tmp) >> found;
	}

	return found;
}
