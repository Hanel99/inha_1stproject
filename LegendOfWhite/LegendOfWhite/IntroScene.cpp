#include "pch.h"
#include "IntroScene.h"
#include "framework.h"

IntroScene::IntroScene()
{
	Init();
}


void IntroScene::Init()
{
	eXMLBtnnum = 0;
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

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	Gdiplus::PointF P;
	std::wstring tempStr;
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));
	Gdiplus::Font F3(L"�������", 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	P.X = 10;
	P.Y = 100;
	tempStr = L"X : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().x);
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 10;
	P.Y = 140;
	tempStr = L"Y : " + std::to_wstring(MouseManager::GetInstance()->GetMousePos().y);
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 200;
	P.Y = 100;
	tempStr = std::to_wstring(eXMLBtnnum);
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);

	MemG->DrawImage(&bm, screenPosRect);
}

void IntroScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT)
	{
		// �ٷ� ���� ����
		SceneManager::GetInstance()->MoveNextScene();
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT + 14 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT + 14 + BTN_HEIGHT)
	{
		//DB���� ������ �ҷ����� �۾� ��ģ �� ���� ����
		SceneManager::GetInstance()->MoveNextScene();
	}
	else if (MouseManager::GetInstance()->GetMousePos().x >= WIDTH / 2 - BTN_WIDTH / 2 && MouseManager::GetInstance()->GetMousePos().x <= WIDTH / 2 + BTN_WIDTH / 2
		&& MouseManager::GetInstance()->GetMousePos().y >= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 && MouseManager::GetInstance()->GetMousePos().y <= HEIGHT / 2 + BTN_HEIGHT * 2 + 28 + BTN_HEIGHT)
	{
		//���� ����
		PostQuitMessage(0);
	}
	else
	{
		
	}
}

void IntroScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
