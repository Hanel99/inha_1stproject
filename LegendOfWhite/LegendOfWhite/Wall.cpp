#include "pch.h"
#include "Wall.h"


void Wall::Update(float Delta)
{
}

void Wall::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 128, 128);

	Gdiplus::Bitmap bm(128, 128, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	wallimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\wall_blue.png"));

	temp.DrawImage(wallimg.lock().get(), rect, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	Gdiplus::Pen P(Gdiplus::Color(255, 0, 0), 5);
	MemG->DrawEllipse(&P, (int)(GetX()), (int)(GetY()), width, height);

	MemG->DrawImage(&bm, screenPosRect);
}
