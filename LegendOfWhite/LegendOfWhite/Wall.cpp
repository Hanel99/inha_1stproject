#include "pch.h"
#include "Wall.h"


Wall::Wall(int getx, int gety)
	: Object(EObjectType::eObjectType_Wall)
{
	SetX(getx);
	SetY(gety);
	width = 60;
	height = 60;
	r = width / 2;
	length = 35; //sqrt(powf(width / 2, 2) + powf(height / 2, 2))�� �����ϴ� 42.42������ ���Խ�. �ʹ� ���������ϸ� ���� ������ �ʾҴµ� �Ѿ������°� �־ �����ѻ������ ����
	center.x = GetX() + r;
	center.y = GetY() + r;
}

Wall::~Wall()
{
}

void Wall::Update(float Delta)
{
}

void Wall::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 128, 128);

	wallimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));
	rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Wall_blue);

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->DrawImage(wallimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
