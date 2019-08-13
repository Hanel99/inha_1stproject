#include "pch.h"
#include "Object.h"
#include "Bullet.h"

void Bullet::Init()
{

}

void Bullet::ProcessInput()
{

}

void Bullet::Update(float Delta)
{
	SetX(GetX() + (Delta * SSPD));
	SetY(GetY() + (Delta * SSPD));
}

void Bullet::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	bulletimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bullet.png"));

	temp.DrawImage(bulletimg.lock().get(),
		rect, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 30, 30);

	MemG->DrawImage(&bm, screenPosRect);

}
