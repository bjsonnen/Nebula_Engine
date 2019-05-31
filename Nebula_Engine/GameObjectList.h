#pragma once

#include "GameObject.h"

#include <map>
#include <vector>
#include <sstream>

namespace NE
{
	class GameObjectList
	{
	public:
		GameObjectList();

		//! Add a new gameobject to the renderqueue
		//! @param object Insert new object here as GameObject
		void Add(NE::GameObject& object);
		//! Remove an exsisting gameobject from the renderqueue
		//! @param object Insert exsisting gameobject here as GameObject
		void Remove(NE::GameObject& object);
		//! Get the current size of the queue
		//! @return Returns the size as int
		int GetSize();
		//! Find the gameobject 
		//! @param object Insert object to search for as GameObject
		NE::GameObject* Find(NE::GameObject& object);
		//! Find the gameobject at index i
		//! @param i Insert index as int
		NE::GameObject* FindAtIndex(int i);

		~GameObjectList();

	private:
		std::map<unsigned int, NE::GameObject*> objectList;
		unsigned int internalSize = 0;

		//! Reads the first int from string
		//! @param s Insert string here as std::string
		//! @return Returns the int from the string
		int ParseInt(std::string s);
	};
}