#pragma once
#include "Singleton.h"
#include "pch.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager();

	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	void SetXMLData(std::vector<Gdiplus::Rect>& rects, EXMLType etype);

	Bullet* CreateBullet();
	void RetrunBullet(Bullet* pBullet);
	Gdiplus::Rect* GetRect(EXMLType, int);

private:
	std::vector<std::pair<bool, Bullet*>> AssetbulletVec;
	std::vector<Gdiplus::Rect> AssetBtnImgVec;
	std::vector<Gdiplus::Rect> AssetObjImgVec;

	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
	//std::unordered_map<size_t, Image*> soundDic;
};

AssetManager* AssetManager::instance = nullptr;