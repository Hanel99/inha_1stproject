#pragma once
#include "Singleton.h"
#include "Object.h"
#include "Player.h"

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	~ObjectManager();

	void Init();


};

ObjectManager* ObjectManager::instance = nullptr;

