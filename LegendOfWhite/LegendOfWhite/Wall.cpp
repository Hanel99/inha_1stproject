#include "pch.h"
#include "Wall.h"


void Wall::Update(float Delta)
{
}

void Wall::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 128, 128);

	//Gdiplus::Bitmap bm(128, 128, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);

	wallimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));
	rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Wall_blue);
	//temp.DrawImage(wallimg.lock().get(), rect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	//Gdiplus::Pen P(Gdiplus::Color(255, 0, 0), 2);
	//MemG->DrawEllipse(&P, (int)(center.x - r), (int)(center.y - r), r * 2, r * 2);

	//Gdiplus::Pen P2(Gdiplus::Color(0, 0, 255), 2);
	//MemG->DrawEllipse(&P2, (int)(center.x - length), (int)(center.y - length), length * 2, length * 2);

	MemG->DrawImage(wallimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
