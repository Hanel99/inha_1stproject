#include "pch.h"
#include "NextStage.h"


NextStage::NextStage(int getx, int gety)
	: Object(EObjectType::eObjectType_NextStage)
{
	Init(getx, gety);
}

NextStage::~NextStage()
{
	Release();
}

void NextStage::Init(int getx, int gety)
{
	SetX(getx);
	SetY(gety);
	width = 64;
	height = 64;
	r = width / 4;
	center.x = GetX() + width / 2;
	center.y = GetY() + width / 2;
}

void NextStage::Release()
{
	
}

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
