#pragma once
#include "Singleton.h"
#include "pch.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager();

	void Init();


};

AssetManager* AssetManager::instance = nullptr;

