#include "pch.h"
#include "NextStage.h"


void NextStage::Update(float Delta)
{
}

void NextStage::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect Imgrc(0, 0, 128, 128);

	Gdiplus::Bitmap bm(128, 128, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	Img = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));

	Gdiplus::Rect* r = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_NextStage);
	temp.DrawImage(Img.lock().get(), Imgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);	

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->DrawImage(&bm, screenPosRect);
}
