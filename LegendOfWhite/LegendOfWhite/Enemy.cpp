#include "pch.h"
#include "Enemy.h"


void Enemy::Update(float Delta)
{
}

void Enemy::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	enemyimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\boss.png"));

	temp.DrawImage(enemyimg.lock().get(),
		rect, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 140, 140);

	MemG->DrawImage(&bm, screenPosRect);
}
