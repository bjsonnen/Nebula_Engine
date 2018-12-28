#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <stdexcept>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* Entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void Update()
	{
		for (int i = 0; i < components.size(); i++) components[i]->Update();
		for (int i = 0; i < components.size(); i++) components[i]->Draw();
	}
	void Draw() {}
	bool IsActive() const { return active; }
	void Destory() { active = false; }

	template<typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		if (HasComponent<T>())
		{
			NE_ERROR_CHECK(NE_COMPONENT_ALREADY);
			T* tmpT(Entity);
			return T();
			// return something else
		}

		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->Entity = this;
		std::unique_ptr<Component> uPtr(c);
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		if (!HasComponent<T>())
			NE_ERROR_CHECK(NE_COMPONENT_NOT_FOUND);

		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void Update()
	{
		for (int i = 0; i < entities.size(); i++) entities[i]->Update();
		//for (auto& e : entities) e->Update();
	}
	void Draw()
	{
		for (int i = 0; i < entities.size(); i++) entities[i]->Draw();
		//for (auto& e : entities) e->Draw();
	}

	void Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->IsActive();
		}), std::end(entities));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};