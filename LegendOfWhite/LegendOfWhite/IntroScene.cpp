#include "pch.h"
#include "IntroScene.h"
#include "framework.h"

IntroScene::IntroScene()
{
}


void IntroScene::Init()
{
}

void IntroScene::ProcessInput()
{
	//������ Ŭ���ϸ� �Ѿ�� �ڵ带 ¥�� ��. ���⼱ �ӽ÷� �̷��� ����
	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
		SceneManager::GetInstance()->MoveNextScene();
	}
}

void IntroScene::Update(float Delta)
{

}

void IntroScene::Render(Gdiplus::Graphics* MemG)
{		
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//Gdiplus::Image tempImg(TEXT("bgaimage.png"));

	introImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\a.png"));


	temp.DrawImage(introImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0,0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
}
