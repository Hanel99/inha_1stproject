#pragma once
#include "Singleton.h"
#include "pch.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();

	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	void SetXMLData(std::vector<Gdiplus::Rect>& Rect, char* fileName);

	Bullet* CreateBullet();
	void RetrunBullet(Bullet* pBullet);

private:
	std::vector<std::pair<bool, Bullet*>> AssetbulletVec;

	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
	//std::unordered_map<size_t, Image*> soundDic;
};

AssetManager* AssetManager::instance = nullptr;