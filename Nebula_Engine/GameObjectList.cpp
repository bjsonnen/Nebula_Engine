#include "GameObjectList.h"



NE::GameObjectList::GameObjectList()
{
}

void NE::GameObjectList::Add(NE::GameObject& object)
{
	//objectList[objectList.size()] = &object;
	//object.SetObjectName("GameObject " + std::to_string(objectList.size()));
	objectList[internalSize] = &object;
	internalSize++;
	object.SetObjectName("GameObject " + std::to_string(internalSize));
}

void NE::GameObjectList::Remove(NE::GameObject& object)
{
	int i = ParseInt(object.GetObjectName());
	objectList[i - 1] = nullptr;
	objectList.erase(i - 1);
}

int NE::GameObjectList::GetSize()
{
	return objectList.size();
}

NE::GameObject * NE::GameObjectList::Find(NE::GameObject& object)
{
	int i = ParseInt(object.GetObjectName());
	return objectList.at(i - 1);
}

NE::GameObject * NE::GameObjectList::FindAtIndex(int i)
{
	if(objectList[i] != nullptr)
		return objectList.at(i);
	return nullptr;
}


NE::GameObjectList::~GameObjectList()
{
}

int NE::GameObjectList::ParseInt(std::string s)
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
