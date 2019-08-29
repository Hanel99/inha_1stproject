#include "pch.h"
#include "AssetManager.h"

#define VEC_LENGTH 1000


AssetManager::AssetManager()
{
	Init();
}

AssetManager::~AssetManager()
{
	Release();
}

void AssetManager::Init()
{
	//메모리 풀을 이용해서 총알로 인한 메모리 파편화를 방지
	AssetbulletVec.reserve(VEC_LENGTH);
	AssetbulletVec.resize(VEC_LENGTH);
	for (int i = 0; i < VEC_LENGTH; ++i)
	{
		bool canuse = true;
		Bullet* b = new Bullet();
		AssetbulletVec[i] = std::pair<bool, Bullet*>(canuse, b);
	}

	SetXMLData(AssetBtnImgVec, eXMLType_Btn);
	SetXMLData(AssetObjImgVec, eXMLType_Obj);

	SoundSystem();
	PlaySound(eSound_BGM);
}

void AssetManager::Release()
{
	for (auto& it : AssetbulletVec)
	{
		delete it.second;
	}
	AssetbulletVec.clear();
	ReleaseSound();
}


Bullet* AssetManager::CreateBullet()
{
	for (auto& it : AssetbulletVec)
	{
		if (it.first)
		{
			it.first = false;
			return it.second;
		}
	}
	return nullptr;
}

void AssetManager::RetrunBullet(Bullet* b)
{
	int i = 0;
	for (auto& it : AssetbulletVec)
	{
		i++;
		if (it.second == b)
		{
			it.first = true;
			it.second->BulletReset();
			break;
		}
	}
}

Gdiplus::Rect* AssetManager::GetRect(EXMLType etype, int i)
{
	switch (etype)
	{
	case eXMLType_Btn:
		return &AssetBtnImgVec[i];
		break;
	case eXMLType_Obj:
		return &AssetObjImgVec[i];
		break;
	}
	return nullptr;
}

void AssetManager::SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(32, FMOD_INIT_NORMAL, NULL);
	
	//BGM Song: Mike Chino - Double Points(Original Mix)
	//Follow Artist : https://soundcloud.com/mike-chino
	//Music promoted by DayDreamSound : https://youtu.be/6jl05TYNQy4

	pSystem->createSound("Asset\\sound\\bgm.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[eSound_BGM]);
	pSystem->createSound("Asset\\sound\\BtnClick.wav", FMOD_DEFAULT, NULL, &pSound[eSound_BtnClick]);
	pSystem->createSound("Asset\\sound\\EnemyDead.wav", FMOD_DEFAULT, NULL, &pSound[eSound_EnemyDead]);
	pSystem->createSound("Asset\\sound\\GameClear.wav", FMOD_DEFAULT, NULL, &pSound[eSound_GameClear]);
	pSystem->createSound("Asset\\sound\\GameOver.wav", FMOD_DEFAULT, NULL, &pSound[eSound_GameOver]);
	pSystem->createSound("Asset\\sound\\NextStage.wav", FMOD_DEFAULT, NULL, &pSound[eSound_NextStage]);
	pSystem->createSound("Asset\\sound\\PlayerDamaged.wav", FMOD_DEFAULT, NULL, &pSound[eSound_PlayerDamaged]);
	pSystem->createSound("Asset\\sound\\Shot.wav", FMOD_DEFAULT, NULL, &pSound[eSound_Shot]);
	pSystem->createSound("Asset\\sound\\EnemyDamaged.wav", FMOD_DEFAULT, NULL, &pSound[eSound_EnemyDamaged]);
}

void AssetManager::PlaySound(int Sound_num)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel[Sound_num]);
}

void AssetManager::ReleaseSound()
{
	pSystem->release();
	pSystem->close();
}


std::weak_ptr<Gdiplus::Image> AssetManager::GetImage(std::wstring str)
{
	//hash는 img에 저장된 고유 인덱스. 아래 MyLoadImage에서 첫 호출시 각각 할당해준다
	std::hash<std::wstring> makeHash;
	std::weak_ptr<Gdiplus::Image> retimg;

	//hash를 통해 imgDic에 있는 img정보를 찾는다.
	auto it = imgDic.find(makeHash(str));

	//만약 현재 imgDic에 없다면 MyLoadImage로 가서 img정보를 저장해준다.
	if (it == imgDic.end())
		retimg = MyLoadImage(str);
	else
		retimg = it->second;

	return retimg;
}



std::weak_ptr<Gdiplus::Image> AssetManager::MyLoadImage(std::wstring fileName)
{
	std::wstring temp(fileName);

	std::shared_ptr<Gdiplus::Image> Img = std::make_shared<Gdiplus::Image>(temp.c_str());
	std::hash<std::wstring> makeHash;
	imgDic.insert(std::make_pair(makeHash(fileName), Img));

	return Img;
}

void AssetManager::SetXMLData(std::vector<Gdiplus::Rect>& rects, EXMLType etype)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	switch (etype)
	{
	case eXMLType_Btn:
		doc->LoadFile("Asset\\btn_spritesheet.xml");
		break;
	case eXMLType_Obj:
		doc->LoadFile("Asset\\obj_spritesheet.xml");
		break;
	}
	if (doc == nullptr) return;

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("SubTexture");

	for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	{
		Gdiplus::Rect r(Gdiplus::Rect(element->IntAttribute("x"), element->IntAttribute("y"),
			element->IntAttribute("width"), element->IntAttribute("height")));
		rects.emplace_back(r);
	}
	delete doc;
}