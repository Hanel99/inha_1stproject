#include "pch.h"
#include "Enemy.h"


void Enemy::Update(float Delta)
{
}

void Enemy::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, 256, 256);

	//Gdiplus::Bitmap bm(256, 256, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);
	enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\boss.png"));

	//temp.DrawImage(enemyimg.lock().get(),
	//	rect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->DrawImage(enemyimg.lock().get(),
		screenPosRect, 0, 0, 256, 256, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
}
