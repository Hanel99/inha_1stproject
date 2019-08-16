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

	SetXMLData(AssetBtnImgVec, eXMLType_Btn);
	SetXMLData(AssetObjImgVec, eXMLType_Obj);
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
	////render에서 이미지를 이렇게 불러와서 xml만큼 따주면 된다.
	//std::weak_ptr<Gdiplus::Image> load = GetImage(TEXT("sokoban_spritesheet.png"));
	//Gdiplus::Rect Dst(0, 0, 116, 164);
	//Gdiplus::Bitmap bm(116, 164, PixelFormat32bppARGB);
	//Gdiplus::Graphics test(&bm);
	////불러온 이미지 load, xml에서 파싱해온 rects. [frame]부분에 enum쓰면 찾기 더 쉬울것
	//test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//
	////실제 그려줄 위치 . x, y, widt, height
	//Gdiplus::Rect Dst2(x, 0, 116, 164);
	//MemG->DrawImage(&bm, Dst2);


	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	switch (etype)
	{
	case eXMLType_Btn:
		doc->LoadFile("Asset\\btn_spritesheet.xml");
		break;
	case eXMLType_Obj:
		doc->LoadFile("Asset\\sokoban_spritesheet.xml");
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
}