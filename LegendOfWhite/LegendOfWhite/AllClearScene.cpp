#include "pch.h"
#include "AllClearScene.h"

AllClearScene::AllClearScene()
{
}

void AllClearScene::Init()
{
}

void AllClearScene::Update(float Delta)
{
}

void AllClearScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect introImgrc(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	allClearImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\AllClearImg.png"));
	temp.DrawImage(allClearImg.lock().get(), introImgrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	
	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(&bm, screenPosRect);
}

void AllClearScene::SendLButtonDown(UINT nFlags, CPoint point)
{
}

void AllClearScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
