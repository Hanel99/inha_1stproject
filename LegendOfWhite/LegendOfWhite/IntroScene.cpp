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
	//원래는 클릭하면 넘어가는 코드를 짜야 함. 여기선 임시로 이렇게 두자
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
