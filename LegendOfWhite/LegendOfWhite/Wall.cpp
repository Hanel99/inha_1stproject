#include "pch.h"
#include "Wall.h"


void Wall::Update(float Delta)
{
}

void Wall::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	wallimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\wall_blue.png"));

	temp.DrawImage(wallimg.lock().get(), rect, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 80, 80);

	MemG->DrawImage(&bm, screenPosRect);
}
