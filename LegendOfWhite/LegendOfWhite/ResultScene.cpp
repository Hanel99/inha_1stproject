#include "pch.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
}

void ResultScene::Init()
{
}

void ResultScene::Update(float Delta)
{
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		SceneManager::GetInstance()->GotoTitleScene();
	}
}

void ResultScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect Imgrc(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	if (SceneManager::GetInstance()->IsGameClear())
		Img = AssetManager::GetInstance()->GetImage(TEXT("Asset\\AllClearImg.png"));
	else
		Img = AssetManager::GetInstance()->GetImage(TEXT("Asset\\Gameover.png"));
	temp.DrawImage(Img.lock().get(), Imgrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(&bm, screenPosRect);

}

void ResultScene::SendLButtonDown(UINT nFlags, CPoint point)
{

}

void ResultScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
