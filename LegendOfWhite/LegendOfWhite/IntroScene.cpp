#include "pch.h"
#include "IntroScene.h"
#include "framework.h"

IntroScene::IntroScene()
{
}


void IntroScene::Init()
{
}

void IntroScene::Update(float Delta)
{

}

void IntroScene::Render(Gdiplus::Graphics* MemG)
{		
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 255, 255, 255));
	MemG->FillRectangle(&WhiteBrush, rect);

	introImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\introImg.png"));


	temp.DrawImage(introImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0,0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
}

void IntroScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	SceneManager::GetInstance()->MoveNextScene();
}
