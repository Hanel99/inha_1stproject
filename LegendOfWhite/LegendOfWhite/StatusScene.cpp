#include "pch.h"
#include "StatusScene.h"

#define _CRT_SECURE_NO_WARNINGS

StatusScene::StatusScene()
{
}

void StatusScene::Init()
{
}

void StatusScene::Update(float Delta)
{
	//°ÔÀÓ¾ÀÀ¸·Î
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	statImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\statImg.png"));

	temp.DrawImage(statImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//±×·ÁÁÙ screenÁÂÇ¥ÀÇ rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Font F(L"¸¼Àº°íµñ", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);	
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));

	P.X = 100.0f;
	P.Y = 10.0f;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = 120.0f;
	P.Y = 20.0f;
	tempStr = L"1pt";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = 200.0f;
	P.Y = 10.0f;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKM) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = 220.0f;
	P.Y = 20.0f;
	tempStr = std::to_wstring((GameData::GetInstance()->ATKM+10) / 5) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);


	// ½ºÅÈ ÁÂÇ¥
	Gdiplus::Rect statrc(STATX_WIDTH, STATY_HEIGHT, STAT_WIDTH, STAT_HEIGHT);
	Gdiplus::Rect statrc2(STATX_WIDTH, STATY_HEIGHT + STAT_HEIGHT + STAT_HITV, STAT_WIDTH, STAT_HEIGHT);
	Gdiplus::Rect statrc3(STATX_WIDTH, STATY_HEIGHT + STAT_HEIGHT * 2 + STAT_HITV * 2, STAT_WIDTH, STAT_HEIGHT);
	Gdiplus::Rect statrc4(STATX_WIDTH, STATY_HEIGHT + STAT_HEIGHT * 3 + STAT_HITV * 3, STAT_WIDTH, STAT_HEIGHT);
	Gdiplus::Rect statrc5(STATX_WIDTH, STATY_HEIGHT + STAT_HEIGHT * 4 + STAT_HITV * 4, STAT_WIDTH, STAT_HEIGHT);

	// ½ºÅÈ ÆÛ¼¾Æ®
	Gdiplus::Rect statPrc(STATPX_WIDTH, STATPY_HEIGHT, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statPrc2(STATPX_WIDTH, STATPY_HEIGHT + STATP_HEIGHT + STATP_HITV, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statPrc3(STATPX_WIDTH, STATPY_HEIGHT + STATP_HEIGHT * 2 + STATP_HITV * 2, STATP_WIDTH, STATP_HEIGHT);

	// ½ºÅÈ ¾÷±×·¹ÀÌµå
	Gdiplus::Rect statUrc(STATUX_WIDTH, STATUY_HEIGHT, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUrc2(STATUX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT + STATP_HITV, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUrc3(STATUX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT * 2 + STATP_HITV * 2, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUrc4(STATUX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT * 3 + STATP_HITV * 3, STATP_WIDTH, STATP_HEIGHT);

	// ½ºÅÈ ¾÷±×·¹ÀÌµå ÆÛ¼¾Æ®
	Gdiplus::Rect statUPrc(STATUPX_WIDTH, STATUY_HEIGHT, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUPrc2(STATUPX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT + STATP_HITV, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUPrc3(STATUPX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT * 2 + STATP_HITV * 2, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUPrc4(STATUPX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT * 3 + STATP_HITV * 3, STATP_WIDTH, STATP_HEIGHT);
	Gdiplus::Rect statUPrc5(STATUPX_WIDTH, STATUY_HEIGHT + STATP_HEIGHT * 4 + STATP_HITV * 4, STATP_WIDTH, STATP_HEIGHT);
	
	// ¿ÞÂÊ ÀÛÀº ½ºÅÈ ¹öÆ°
	Gdiplus::Rect lminiStatrc(LMINISTATX_WIDTH, LMINISTATY_HEIGHT, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect lminiStatrc2(LMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT + MINISTAT_HITV, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect lminiStatrc3(LMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT * 2 + MINISTAT_HITV * 2, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect lminiStatrc4(LMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT * 3 + MINISTAT_HITV * 3, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);

	// ¿À¸¥ÂÊ ÀÛÀº ½ºÅÈ ¹öÆ°
	Gdiplus::Rect rminiStatrc(RMINISTATX_WIDTH, LMINISTATY_HEIGHT, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect rminiStatrc2(RMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT + MINISTAT_HITV, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect rminiStatrc3(RMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT * 2 + MINISTAT_HITV * 2, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect rminiStatrc4(RMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT * 3 + MINISTAT_HITV * 3, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);
	Gdiplus::Rect rminiStatrc5(RMINISTATX_WIDTH, LMINISTATY_HEIGHT + LMINISTAT_HEIGHT * 4 + MINISTAT_HITV * 4, LMINISTAT_WIDTH, LMINISTAT_HEIGHT);



	// ½ºÅÈ ÁËÇ¥
	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));
	temp.DrawImage(bgImg.lock().get(),
		statrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));
	temp.DrawImage(bgImg.lock().get(),
		statrc2, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statrc3, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statrc4, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statrc5, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	// ½ºÅÈ ÆÛ¼¾Æ®
	temp.DrawImage(bgImg.lock().get(),
		statPrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statPrc2, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statPrc3, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	// ½ºÅÈ ¾÷±×·¹ÀÌµå
	temp.DrawImage(bgImg.lock().get(),
		statUrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUrc2, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUrc3, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUrc4, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	// ½ºÅÈ ¾÷±×·¹ÀÌµå ÆÛ¼¾Æ®
	temp.DrawImage(bgImg.lock().get(),
		statUPrc, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUPrc2, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUPrc3, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUPrc4, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		statUPrc5, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	// ¿ÞÂÊ ÀÛÀº ½ºÅÈ ¹öÆ°
	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\wall_blue.png"));
	temp.DrawImage(bgImg.lock().get(),
		lminiStatrc, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		lminiStatrc2, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		lminiStatrc3, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		lminiStatrc4, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	// ¿À¸¥ÂÊ ÀÛÀº ½ºÅÈ ¹öÆ°
	temp.DrawImage(bgImg.lock().get(),
		rminiStatrc, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		rminiStatrc2, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		rminiStatrc3, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		rminiStatrc4, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	temp.DrawImage(bgImg.lock().get(),
		rminiStatrc5, 0, 0, 128, 128, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);


	



	//for (auto& it : objectVec)
	//{
		//it->Render(MemG);
	//}

	MemG->DrawImage(&bm, screenPosRect);
}

void StatusScene::SendLButtonDown(UINT nFlags, CPoint point)
{
}

void StatusScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
