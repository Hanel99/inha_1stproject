#include "pch.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
}


void IntroScene::Init()
{
}

void IntroScene::Control()
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

void IntroScene::Render(Gdiplus::Graphics G)
{
}
