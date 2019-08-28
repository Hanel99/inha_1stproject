#pragma once
#include "Singleton.h"
#include "pch.h"


class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager();

	void Init();

	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	void SetXMLData(std::vector<Gdiplus::Rect>& rects, EXMLType etype);

	Bullet* CreateBullet();
	void RetrunBullet(Bullet* pBullet);
	Gdiplus::Rect* GetRect(EXMLType, int);

	FMOD::System* pSystem;
	FMOD::Sound* pSound[9];
	FMOD::Channel* pChannel[18];

	void SoundSystem();
	void PlaySound(int Sound_num);
	void ReleaseSound();
	void StopSound(int Sound_num);

private:
	std::vector<std::pair<bool, Bullet*>> AssetbulletVec;
	std::vector<Gdiplus::Rect> AssetBtnImgVec;
	std::vector<Gdiplus::Rect> AssetObjImgVec;

	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
};

AssetManager* AssetManager::instance = nullptr;