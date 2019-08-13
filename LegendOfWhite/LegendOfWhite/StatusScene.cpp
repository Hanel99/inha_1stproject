#include "pch.h"
#include "StatusScene.h"

StatusScene::StatusScene()
{
}

void StatusScene::Init()
{
}

void StatusScene::ProcessInput()
{
	//게임씬으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
}

void StatusScene::Update(float Delta)
{
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	statImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\a.png"));

	temp.DrawImage(statImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);

	//for (auto& it : objectVec)
	//{
		//it->Render(MemG);
	//}
}
