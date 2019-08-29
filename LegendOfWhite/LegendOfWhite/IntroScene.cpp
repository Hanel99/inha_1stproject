#include "pch.h"
#include "IntroScene.h"
#include "framework.h"
#include "Player.h"

IntroScene::IntroScene()
{
	Init();
}

IntroScene::~IntroScene()
{
	Release();
}

void IntroScene::Init()
{
	eXMLBtnnum = 0;	

	//메모리릭 번호 
	//_crtBreakAlloc = 1200;
}

void IntroScene::Release()
{
	
}


void IntroScene::Update(float Delta)
{
	if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT)
	{
		eXMLBtnnum = eXMLBtnnum_Newplayh;
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT + 14 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT + 14 + BTN_HEIGHT)
	{
		eXMLBtnnum = eXMLBtnnum_Loadplayh;
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 + BTN_HEIGHT)
	{
		eXMLBtnnum = eXMLBtnnum_Gameendh;
	}
	else
	{
		eXMLBtnnum = 0;
	}
}

void IntroScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect introImgrc(0, 0, WIDTH, HEIGHT);
	Gdiplus::Rect newplayImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2, BTN_WIDTH, BTN_HEIGHT);
	Gdiplus::Rect loadplayImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2 + BTN_HEIGHT + 14, BTN_WIDTH, BTN_HEIGHT);
	Gdiplus::Rect gameendImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2 + BTN_HEIGHT * 2 + 28, BTN_WIDTH, BTN_HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);


	introImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\introImg.jpg"));
	temp.DrawImage(introImg.lock().get(), introImgrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	btnImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\btn_spritesheet.png"));
	if (eXMLBtnnum == eXMLBtnnum_Newplayh)
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Newplayh);
	else
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Newplay);	
	temp.DrawImage(btnImg.lock().get(), newplayImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	if (eXMLBtnnum == eXMLBtnnum_Loadplayh)
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Loadplayh);
	else
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Loadplay);
	temp.DrawImage(btnImg.lock().get(), loadplayImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	if (eXMLBtnnum == eXMLBtnnum_Gameendh)
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Gameendh);
	else
		r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Gameend);
	temp.DrawImage(btnImg.lock().get(), gameendImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
}

void IntroScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT)
	{
		// DB 초기화 뒤 게임 시작
		AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
		GameData::GetInstance()->SaveFirstPlayerData();
		GameData::GetInstance()->LoadPlayerData();
		GameData::GetInstance()->SetPlayerDBData();
		
		SceneManager::GetInstance()->isComeGameScene = true;
		SceneManager::GetInstance()->MoveNextScene();
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT + 14 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT + 14 + BTN_HEIGHT)
	{
		//DB에서 데이터 불러오는 작업 거친 뒤 게임 시작
		AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
		GameData::GetInstance()->LoadPlayerData();
		GameData::GetInstance()->SetPlayerDBData();
		
		SceneManager::GetInstance()->isComeGameScene = true;
		SceneManager::GetInstance()->MoveNextScene();
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 + BTN_HEIGHT)
	{
		//게임 끄기
		AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
		Release();
		GameData::GetInstance()->Release();
		SceneManager::GetInstance()->Release();
		PostQuitMessage(0);
	}
	else
	{
		//아무것도 아님
	}
}

void IntroScene::SendRButtonDown(UINT nFlags, CPoint point)
{

}
