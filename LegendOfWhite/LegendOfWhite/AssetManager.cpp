#include "pch.h"
#include "AssetManager.h"

#define VEC_LENGTH 1000

AssetManager::AssetManager()
{	
	//�޸� Ǯ�� �̿��ؼ� �Ѿ˷� ���� �޸� ����ȭ�� ����
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
	//hash�� img�� ����� ���� �ε���. �Ʒ� MyLoadImage���� ù ȣ��� ���� �Ҵ����ش�
	std::hash<std::wstring> makeHash;
	std::weak_ptr<Gdiplus::Image> retimg;

	//hash�� ���� imgDic�� �ִ� img������ ã�´�.
	auto it = imgDic.find(makeHash(str));

	//���� ���� imgDic�� ���ٸ� MyLoadImage�� ���� img������ �������ش�.
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
	////render���� �̹����� �̷��� �ҷ��ͼ� xml��ŭ ���ָ� �ȴ�.
	//std::weak_ptr<Gdiplus::Image> load = GetImage(TEXT("sokoban_spritesheet.png"));
	//Gdiplus::Rect Dst(0, 0, 116, 164);
	//Gdiplus::Bitmap bm(116, 164, PixelFormat32bppARGB);
	//Gdiplus::Graphics test(&bm);
	////�ҷ��� �̹��� load, xml���� �Ľ��ؿ� rects. [frame]�κп� enum���� ã�� �� �����
	//test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//
	////���� �׷��� ��ġ . x, y, widt, height
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