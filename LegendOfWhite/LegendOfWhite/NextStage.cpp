#include "pch.h"
#include "NextStage.h"

void NextStage::Update(float Delta)
{
}

void NextStage::Render(Gdiplus::Graphics* MemG)
{
	//출발지점 정해줘야함
	Gdiplus::Rect Imgrc(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Img = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));
	//Img = AssetManager::GetInstance()->GetImage(TEXT("Asset\\ground_01.png"));
	Gdiplus::Rect* r = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_NextStage);
	//temp.DrawImage(Img.lock().get(), Imgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(Img.lock().get(), Imgrc, 0, 0, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	//temp.DrawImage(Img.lock().get(), Imgrc, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 64, 64);

	MemG->DrawImage(&bm, screenPosRect);
}
