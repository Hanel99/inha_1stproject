#include "pch.h"
#include "Wall.h"


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

	//Gdiplus::Pen P(Gdiplus::Color(255, 0, 0), 2);
	//MemG->DrawEllipse(&P, (int)(center.x - r), (int)(center.y - r), r * 2, r * 2);
}
