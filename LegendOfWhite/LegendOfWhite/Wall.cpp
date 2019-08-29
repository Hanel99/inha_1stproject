#include "pch.h"
#include "Wall.h"


Wall::Wall(int getx, int gety)
	: Object(EObjectType::eObjectType_Wall)
{
	Init(getx, gety);
}

Wall::~Wall()
{
	Release();
}

void Wall::Init(int getx, int gety)
{
	SetX(getx);
	SetY(gety);
	width = 60;
	height = 60;
	r = width / 2;

	//length�� �������� ������ ��. sqrt(powf(width / 2, 2) + powf(height / 2, 2)) ���갪�̰�, ������ 42.42������ ���Խ�.
	//�ʹ� ���������ϸ� ���� ������ �ʾҴµ� �Ѿ������°� �־ �����ѻ������ ����
	length = 35;
	
	center.x = GetX() + r;
	center.y = GetY() + r;
}

void Wall::Release()
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
