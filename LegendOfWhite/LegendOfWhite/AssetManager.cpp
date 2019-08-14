#include "pch.h"
#include "AssetManager.h"

#define VEC_LENGTH 1000

AssetManager::AssetManager()
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
	for (auto& it : AssetbulletVec)
	{
		if (it.second == b)
		{
			it.first = true;
			it.second->BulletReset();
		}
	}
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



void AssetManager::SetXMLData(std::vector<Gdiplus::Rect>& Rects, char* fileName)
{
	//일단은 냅둠.. 나중에 쓸수도 있으니까

	//char* temp = "XML\\";
	//strcat_s(temp, fileName);
	//strcat_s(&temp, fileName);

	//tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	//doc->LoadFile(fileName);

	//if (doc == nullptr) return;

	//tinyxml2::XMLElement* Root = doc->RootElement();
	////tinyxml2::XMLElement* TextureAtlasInfo = Root->FirstChildElement("TextureAtlas");
	//tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("sprite");

	//for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	//{
	//	Gdiplus::Rect r(Gdiplus::Rect(element->IntAttribute("x"), element->IntAttribute("y"),
	//		element->IntAttribute("w"), element->IntAttribute("h")));
	//	Rects.emplace_back(r);
	//}

}