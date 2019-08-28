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
	length = 35; //sqrt(powf(width / 2, 2) + powf(height / 2, 2))를 연산하니 42.42정도가 나왔슴. 너무 외적으로하면 벽에 닿지도 않았는데 총알터지는게 있어서 적당한사이즈로 줄임
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

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->DrawImage(wallimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
