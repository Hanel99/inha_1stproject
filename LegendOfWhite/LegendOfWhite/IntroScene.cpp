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

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 255, 255, 255));
	MemG->FillRectangle(&WhiteBrush, rect);

	introImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\introImg.png"));


	temp.DrawImage(introImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0,0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
}