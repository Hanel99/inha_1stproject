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


void IntroScene::Render(Gdiplus::Graphics * MemG)
{
	Gdiplus::Rect introImgrc(0, 0, WIDTH, HEIGHT);
	Gdiplus::Rect newplayImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2, BTN_WIDTH, BTN_HEIGHT);
	Gdiplus::Rect loadplayImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2 + BTN_HEIGHT + 14, BTN_WIDTH, BTN_HEIGHT);
	Gdiplus::Rect gameendImgrc(WIDTH / 2 - BTN_WIDTH / 2, HEIGHT / 2 + BTN_HEIGHT * 2 + 28, BTN_WIDTH, BTN_HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	introImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\introImg.png"));
	temp.DrawImage(introImg.lock().get(), introImgrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	btnImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\btn_spritesheet.png"));
	Gdiplus::Rect* r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Newplay);
	temp.DrawImage(btnImg.lock().get(), newplayImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Loadplay);
	temp.DrawImage(btnImg.lock().get(), loadplayImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	r = AssetManager::GetInstance()->GetRect(eXMLType_Btn, eXMLBtnnum_Gameend);
	temp.DrawImage(btnImg.lock().get(), gameendImgrc, r->X, r->Y, r->Width, r->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);
}

void IntroScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	SceneManager::GetInstance()->MoveNextScene();
}
